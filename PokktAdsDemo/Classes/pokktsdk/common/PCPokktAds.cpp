#include "PCPokktAds.h"
#include "PCConstants.h"
#include <string>
#include <sstream>
#include "../cajun/json/writer.h"
#include "../cajun/json/reader.h"
#include "../cajun/json/elements.h"


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "../androidExt/PCAndroidExtension.h"

#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "IOSExtension.h"

#endif


#define EVENT_AD_CACHING_COMPLETED          "AdCachingCompleted"
#define EVENT_AD_CACHING_FAILED             "AdCachingFailed"
#define EVENT_AD_CLOSED                     "AdClosed"
#define EVENT_AD_COMPLETED                  "AdCompleted"
#define EVENT_AD_DISPLAYED                  "AdDisplayed"
#define EVENT_AD_SKIPPED                    "AdSkipped"
#define EVENT_AD_GRATIFIED                  "AdGratified"
#define EVENT_AD_AVAILABILITY               "AdAvailability"
#define EVENT_AD_FAILED_TO_SHOW             "AdFailedToShow"


#define VIDEO           "0"
#define INTERSTITIAL    "3"
#define BANNER          "1"


using namespace pokkt;

std::map<std::string, PCPokktAds::ListenerTargetPairAdEvent*> PCPokktAds::_eventMapAdEvent;

// to_string() helper
template<typename T>
std::string to_string(const T& t)
{
    std::ostringstream os;
    os << t;
    return os.str();
}

void PCPokktAds::setPokktConfig(std::string appId, std::string secKey)
{
    json::Object jsonObject;
    
    jsonObject["appId"] = json::String(appId);
    jsonObject["securityKey"] = json::String(secKey);
    
    std::stringstream strStream;
    json::Writer::Write(jsonObject, strStream);
    notifyNative(SET_POKKT_CONFIG_OP, strStream.str().c_str());
}

void PCPokktAds::trackIAP(IAPDetails iapDetails)
{
    json::Object jsonObject;
    
    jsonObject["currencyCode"] = json::String(iapDetails.currencyCode);
    jsonObject["description"] = json::String(iapDetails.description);
    jsonObject["productId"] = json::String(iapDetails.productId);
    jsonObject["price"] = json::String(to_string(iapDetails.price));
    jsonObject["title"] = json::String(iapDetails.title);
    
    std::stringstream strStream;
    json::Writer::Write(jsonObject, strStream);
    notifyNative(ANALYTICS_TRACK_IAP_OP, strStream.str().c_str());
}

void PCPokktAds::setAnalyticDetail(PCPokktAnalyticsDetail analyticDetail)
{
    json::Object jsonObject;
    
    jsonObject["googleAnalyticsID"] = json::String(analyticDetail.googleTrackerID);
    jsonObject["mixPanelProjectToken"] = json::String(analyticDetail.mixPanelTrackerID);
    jsonObject["flurryApplicationKey"] = json::String(analyticDetail.flurryTrackerID);
    jsonObject["selectedAnalyticsType"] = json::String(analyticDetail.eventType);
    
    std::stringstream strStream;
    json::Writer::Write(jsonObject, strStream);
    notifyNative(ANALYTICS_SET_DETAILS_OP, strStream.str().c_str());
}

void PCPokktAds::loadBannerWithRect(std::string screenName, int width, int height, int x, int y)
{
    json::Object jsonObject;
    jsonObject["screenName"] = json::String(screenName);
    jsonObject["width"] = json::String(to_string(width));
    jsonObject["height"] = json::String(to_string(height));
    
    jsonObject["x"] = json::String(to_string(x));
    jsonObject["y"] = json::String(to_string(y));

    
    std::stringstream strStream;
    json::Writer::Write(jsonObject, strStream);
    notifyNative(LOAD_BANNER_WITH_RECT_OP, strStream.str().c_str());
}

void PCPokktAds::loadBanner(std::string screenName, int position)
{
    json::Object jsonObject;
    jsonObject["screenName"] = json::String(screenName);
    jsonObject["bannerPosition"] = json::String(to_string(position));
    
    std::stringstream strStream;
    json::Writer::Write(jsonObject, strStream);
    notifyNative(LOAD_BANNER_OP, strStream.str().c_str());
}

void PCPokktAds::setAdPlayerViewConfig(PCPokktAdPlayerViewConfig playerConfig)
{
    json::Object jsonObject;
    
    jsonObject["shouldAllowSkip"] = json::String(to_string(playerConfig.shouldAllowSkip));
    jsonObject["defaultSkipTime"] = json::String(to_string(playerConfig.defaultSkipTime));
    jsonObject["skipConfirmMessage"] = json::String(playerConfig.skipConfirmMessage);
    jsonObject["shouldAllowMute"] = json::String(to_string(playerConfig.shouldAllowMute));
    jsonObject["shouldSkipConfirm"] = json::String(to_string(playerConfig.shouldConfirmSkip));
    jsonObject["skipConfirmYesLabel"] = json::String(playerConfig.skipConfirmYesLabel);
    jsonObject["skipConfirmNoLabel"] = json::String(playerConfig.skipConfirmNoLabel);
    jsonObject["skipTimerMessage"] = json::String(playerConfig.skipTimerMessage);
    jsonObject["incentiveMessage"] = json::String(playerConfig.incentiveMessage);
    
    std::stringstream strStream;
    json::Writer::Write(jsonObject, strStream);
    notifyNative(SET_PLAYER_VIEW_CONFIG_OP, strStream.str().c_str());
}

void PCPokktAds::handleNativeMessage(std::string operation, std::string param)
{
    POKKTLOG("[POKKT-CPP] message received! operation: %s, param: %s", operation.c_str(), param.c_str());
    
    json::Object jsonObject;
    std::stringstream strStream;
    strStream << param;
    json::Reader::Read(jsonObject, strStream);
    
    json::String& screenNameObject = jsonObject["SCREEN_NAME"];
    json::String& isRewardedObject = jsonObject["IS_REWARDED"];
    json::String& adFormatObject = jsonObject["AD_FORMAT"];
    json::String& argsObject = jsonObject["ARGS"];
    
    std::string screenName = screenNameObject.Value();
    bool isReady = isRewardedObject.Value().compare("true") == 0;
    std::string adFormat = adFormatObject.Value();
    std::string args = argsObject.Value();
    
    // process valid operation
    std::string adOperation = "";
    if (adFormat.compare(VIDEO) == 0)
    {
        if (operation.compare(EVENT_AD_CACHING_COMPLETED) == 0)
        {
            adOperation = EVENT_VIDEO_AD_CACHING_COMPLETED;
        }
        else if (operation.compare(EVENT_AD_CACHING_FAILED) == 0)
        {
            adOperation = EVENT_VIDEO_AD_CACHING_FAILED;
        }
        else if(operation.compare(EVENT_AD_CLOSED) == 0)
        {
            adOperation = EVENT_VIDEO_AD_CLOSED;
        }
        else if(operation.compare(EVENT_AD_COMPLETED) == 0)
        {
            adOperation = EVENT_VIDEO_AD_COMPLETED;
        }
        else if(operation.compare(EVENT_AD_FAILED_TO_SHOW) == 0)
        {
            adOperation = EVENT_VIDEO_AD_FAILED_TO_SHOW;
        }
        else if(operation.compare(EVENT_AD_DISPLAYED) == 0)
        {
            adOperation = EVENT_VIDEO_AD_DISPLAYED;
        }
        else if(operation.compare(EVENT_AD_SKIPPED) == 0)
        {
            adOperation = EVENT_VIDEO_AD_SKIPPED;
        }
        else if(operation.compare(EVENT_AD_GRATIFIED) == 0)
        {
            adOperation = EVENT_VIDEO_AD_GRATIFIED;
        }
        else if(operation.compare(EVENT_AD_AVAILABILITY) == 0)
        {
            adOperation = EVENT_VIDEO_AD_AVAILABILITY;
        }
    }
    else if(adFormat.compare(INTERSTITIAL) == 0)
    {
        if(operation.compare(EVENT_AD_CACHING_COMPLETED) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_CACHING_COMPLETED;
        }
        else if(operation.compare(EVENT_AD_CACHING_FAILED) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_CACHING_FAILED;
        }
        else if(operation.compare(EVENT_AD_CLOSED) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_CLOSED;
        }
        else if(operation.compare(EVENT_AD_COMPLETED) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_COMPLETED;
        }
        else if(operation.compare(EVENT_AD_FAILED_TO_SHOW) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_FAILED_TO_SHOW;
        }
        else if(operation.compare(EVENT_AD_DISPLAYED) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_DISPLAYED;
        }
        else if(operation.compare(EVENT_AD_SKIPPED) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_SKIPPED;
        }
        else if(operation.compare(EVENT_AD_GRATIFIED) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_GRATIFIED;
        }
        else if(operation.compare(EVENT_AD_AVAILABILITY) == 0)
        {
            adOperation = EVENT_INTERSTITIAL_AVAILABILITY;
        }
    }
    else
    {
        adOperation = operation;
    }
    
    if (adOperation.length() >= 1)
    {
        ListenerTargetPairAdEvent* l = _eventMapAdEvent[adOperation];
        if (l != NULL)
        {
            EVT_SELECTOR_ADS_EVENT listener = l->listener;
            cocos2d::CCObject *target = l->target;
            
            (target->*listener)(screenName, isReady, args);
        }
    }
}

void PCPokktAds::setAdEventListener(std::string eventName, EVT_SELECTOR_ADS_EVENT listener, cocos2d::CCObject *target)
{
    ListenerTargetPairAdEvent* pair = new ListenerTargetPairAdEvent();
    pair->listener = listener;
    pair->target = target;
    _eventMapAdEvent[eventName] = pair;
}

void PCPokktAds::removeAdEventListener(std::string eventName)
{
    CC_SAFE_DELETE(_eventMapAdEvent[eventName]);
    _eventMapAdEvent[eventName] = NULL;
}

void PCPokktAds::notifyNative(std::string operation, std::string param)
{
    POKKTLOG("[POKKT-CPP] notifying native of operation: %s", operation.c_str());
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    notifyAndroid(operation, param);
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    notifyIOS(operation.c_str(), param.c_str());
    
#endif
}

std::string PCPokktAds::getSDKVersionOnNative()
{
    POKKTLOG("[POKKT-CPP] getting sdk version on native...");
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    return getSDKVersionOnAndroid();
    
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    
    return getSDKVersionOnIOS();
    
#endif
    return "";
}




