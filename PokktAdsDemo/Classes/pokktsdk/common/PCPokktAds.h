#ifndef PCPokktAds_h
#define PCPokktAds_h

#include <stdio.h>
#include "cocos2d.h"
#include "IAPDetails.h"
#include "PCPokktAnalyticsDetails.h"
#include "PCPokktAdPlayerViewConfig.h"

namespace pokkt
{
#define POKKTLOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)
    
    
    typedef void (cocos2d::CCObject::*EVT_SELECTOR_ADS_EVENT)(std::string, bool, std::string);
#define PC_ADS_EVENT_SELECTOR(_SELECTOR) (EVT_SELECTOR_ADS_EVENT)(&_SELECTOR)

    
    /**
     * various pokkt-operations
     **/
#define SET_POKKT_CONFIG_OP                "setPokktConfig"
#define SET_THIRDPARTY_ID_OP               "setThirdPartyUserId"
#define SET_PLAYER_VIEW_CONFIG_OP          "setAdPlayerViewConfig"
#define SET_USER_DETAILS_OP                "setUserDetails"
    
#define VIDEO_CACHE_REWARDED_OP                     "VideoAd.cacheRewarded"
#define VIDEO_SHOW_REWARDED_OP                      "VideoAd.showRewarded"
#define VIDEO_CACHE_NONREWARDED_OP                  "VideoAd.cacheNonRewarded"
#define VIDEO_SHOW_NONREWARDED_OP                   "VideoAd.showNonRewarded"
#define VIDEO_CHECK_REWARDED_AVAILABILITY_OP        "VideoAd.checkAdAvailability.rewarded"
#define VIDEO_CHECK_NONOREWARDED_AVAILABILITY_OP    "VideoAd.checkAdAvailability.nonRewarded"
    
#define INTERSTITIAL_CACHE_REWARDED_OP                  "Interstitial.cacheRewarded"
#define INTERSTITIAL_SHOW_REWARDED_OP                   "Interstitial.showRewarded"
#define INTERSTITIAL_CACHE_NONREWARDED_OP               "Interstitial.cacheNonRewarded"
#define INTERSTITIAL_SHOW_NONREWARDED_OP                "Interstitial.showNonRewarded"
#define INTERSTITIAL_CHECK_REWARDED_AVAILABILITY_OP     "Interstitial.checkAdAvailability.rewarded"
#define INTERSTITIAL_CHECK_NONREWARDED_AVAILABILITY_OP  "Interstitial.checkAdAvailability.nonRewarded"
    
#define LOAD_BANNER_OP                      "Banner.loadBanner"
#define LOAD_BANNER_WITH_RECT_OP            "Banner.loadBannerWithRect"
#define BANNER_DESTROY_OP                   "Banner.destroyBanner"
#define BANNER_SHOULD_AUTO_REFRESH_OP       "Banner.shouldAutoRefresh"
    
#define ANALYTICS_SET_DETAILS_OP           "Analytics.setAnalyticsDetails"
#define ANALYTICS_TRACK_IAP_OP             "Analytics.trackIAP"
#define ANALYTICS_NOTIFY_APP_INSTALL_OP    "Analytics.notifyAppInstall"
#define ANALYTICS_UPDATE_IGA_DATA_OP       "Analytics.updateIGAData"
    
#define DEBUGGING_SHOULD_DEBUG_OP          "Debugging.shouldDebug"
#define DEBUGGING_EXPORT_LOG_OP            "Debugging.exportLog"
#define DEBUGGING_EXPORT_LOG_TO_CLOUD_OP   "Debugging.exportLogToCloud"
#define DEBUGGING_SHOW_TOAST_OP            "Debugging.showToast"
#define DEBUGGING_SHOW_LOG_OP              "Debugging.showLog"
    
    
    class PCPokktAds
    {
    public:
        
        /**
         * Pokkt standard APIs
         **/
        static void setPokktConfig(std::string appId, std::string secKey);
        inline static void setThirdPartyId(std::string thirdPartyId) { notifyNative(SET_THIRDPARTY_ID_OP, thirdPartyId); }
        static void setAdPlayerViewConfig(PCPokktAdPlayerViewConfig playerConfig);
        // TODO: set user details
        inline static std::string getSDKVersion() { return getSDKVersionOnNative(); }
        
        
        /**
         * Video ads related APIs
         **/
        inline static void cacheRewardedVideoAd(std::string message) { notifyNative(VIDEO_CACHE_REWARDED_OP, message); }
        inline static void showRewardedVideoAd(std::string message) { notifyNative(VIDEO_SHOW_REWARDED_OP, message); }
        inline static void cacheNonRewardedVideoAd(std::string message) { notifyNative(VIDEO_CACHE_NONREWARDED_OP, message); }
        inline static void showNonRewardedVideoAd(std::string message) { notifyNative(VIDEO_SHOW_NONREWARDED_OP, message); }
        inline static void checkRewardedVideoAdAvailability(std::string message) { notifyNative(VIDEO_CHECK_REWARDED_AVAILABILITY_OP, message); }
        inline static void checkNonRewardedVideoAdAvailability(std::string message) { notifyNative(VIDEO_CHECK_NONOREWARDED_AVAILABILITY_OP, message); }
        
        
        /**
         * Interstitial related APIs
         **/
        inline static void cacheRewardedInterstitialAd(std::string message) { notifyNative(INTERSTITIAL_CACHE_REWARDED_OP, message); }
        inline static void showRewardedInterstitialAd(std::string message) { notifyNative(INTERSTITIAL_SHOW_REWARDED_OP, message); }
        inline static void cacheNonRewardedInterstitialAd(std::string message) { notifyNative(INTERSTITIAL_CACHE_NONREWARDED_OP, message); }
        inline static void showNonRewardedInterstitialAd(std::string message) { notifyNative(INTERSTITIAL_SHOW_NONREWARDED_OP, message); }
        inline static void checkRewardedInterstitialAdAvailability(std::string message) { notifyNative(INTERSTITIAL_CHECK_REWARDED_AVAILABILITY_OP, message); }
        inline static void checkNonRewardedInterstitialAdAvailability(std::string message) { notifyNative(INTERSTITIAL_CHECK_NONREWARDED_AVAILABILITY_OP, message); }
        
        
        /**
         * Banner related APIs
         * Note: can have only one banner.
         **/
        static void loadBanner(std::string screenName, int position);
        static void loadBannerWithRect(std::string screenName, int width, int height, int x, int y);
        inline static void destroyBanner() { notifyNative(BANNER_DESTROY_OP); }
        inline static void setBannerAutoRefresh(std::string isRefresh) { notifyNative(BANNER_SHOULD_AUTO_REFRESH_OP, isRefresh); }
        
        
        /**
         * Analytics related APIs
         **/
        static void trackIAP(IAPDetails iapDetails);
        static void setAnalyticDetail(PCPokktAnalyticsDetail analyticDetail);
        
        
        /**
         * Debugging related APIs
         **/
        inline static void shouldDebug(bool value) { notifyNative(DEBUGGING_SHOULD_DEBUG_OP, value ? "true" : "false"); }
        inline static void exportLog() { notifyNative(DEBUGGING_EXPORT_LOG_OP); }
        inline static void showToast(std::string message) { notifyNative(DEBUGGING_SHOW_TOAST_OP, message); }
        inline static void showLog(std::string message) { notifyNative(DEBUGGING_SHOW_LOG_OP, message); }
        
        
        /**
         * sets a listener for an event (only one listener per event)
         **/
        static void setAdEventListener(std::string eventName, EVT_SELECTOR_ADS_EVENT listener, cocos2d::CCObject *target);
        static void removeAdEventListener(std::string eventName);
        
        
        /**
         * handle messages via native (java/obj-c)
         **/
        static void handleNativeMessage(std::string operation, std::string param);
        
        
        ~PCPokktAds(){}
        
    private:
                
        typedef struct __listenerTargetPairAdEvent
        {
            EVT_SELECTOR_ADS_EVENT listener;
            cocos2d::CCObject *target;
        } ListenerTargetPairAdEvent;
        
        static std::map<std::string, ListenerTargetPairAdEvent*> _eventMapAdEvent;
        
        // use this to notify native pokkt runtime
        static void notifyNative(std::string operation, std::string param = "");
        
        // sdk version
        static std::string getSDKVersionOnNative();
    };
}

#endif /* PCPokktAds_h */
