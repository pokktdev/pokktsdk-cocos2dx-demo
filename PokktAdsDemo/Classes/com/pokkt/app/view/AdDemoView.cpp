#include "AdDemoView.h"


bool rewardedAdShowRequested = false;
static AdDemoView* viewInstance1 = NULL;
static AdDemoView* viewInstance2 = NULL;

bool AdDemoView::init()
{
    if (!BaseView::init())
        return false;
    
    _coinsEarned = 0;
    
    logo->setPosition(logo->getPosition().x, logo->getPosition().y + 100);
    
    int yPos = logo->getPosition().y - logo->getBoundingBox().size.height / 2;
    
    _txtScreenName = createLabel("<screen name>", 25, Color3B::WHITE, Vec2(visibleSize.width / 2, yPos));
    _txtScreenName->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtScreenName);
    
    yPos -= 100;
    
    _txtPointsEarned = BaseView::createLabel("Points Earned: 0", 35, Color3B::BLACK, Vec2(visibleSize.width / 2, yPos));
    _txtPointsEarned->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtPointsEarned);
    
    yPos -= 100;
    
    _txtStatus = createLabel("<perform an action>", 25, Color3B::WHITE, Vec2(visibleSize.width / 2, yPos));
    _txtStatus->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtStatus);
    
    yPos -= 120;
    
    _btnCacheVideoAd = createButton("Cache Video Ad", CC_CALLBACK_1(AdDemoView::handleCacheVideoAd, this), "button_purple.png");
    _btnCacheVideoAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnCacheVideoAd);
    
    yPos -= 100;
    
    _btnCacheInterstitialAd = createButton("Cache Interstital Ad", CC_CALLBACK_1(AdDemoView::handleCacheInterstitialAd, this));
    _btnCacheInterstitialAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnCacheInterstitialAd);
    
    yPos -= 100;
    
    _btnShowVideoAd = createButton("Show Video Ad", CC_CALLBACK_1(AdDemoView::handleShowVideoAd, this), "button_purple.png");
    _btnShowVideoAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnShowVideoAd);
    
    yPos -= 100;
    
    _btnShowInterstitialAd = createButton("Show Interstital Ad", CC_CALLBACK_1(AdDemoView::handleShowInterstitialAd, this));
    _btnShowInterstitialAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnShowInterstitialAd);
    
    yPos -= 100;
    
    _btnExportLog = createButton("Export Log", CC_CALLBACK_1(AdDemoView::handleExportLog, this));
    _btnExportLog->setPosition(Vec2(visibleSize.width / 2, yPos));
    _btnExportLog->setScale(0.7f);
    this->addChild(_btnExportLog);
    
    // listen for pokkt events
    PCPokktManager::setAdEventListener(AD_AVAILABILITY_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdAvailability), this);
    PCPokktManager::setAdEventListener(AD_CACHING_COMPLETED_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdCachingCompleted), this);
    PCPokktManager::setAdEventListener(AD_CACHING_FAILED_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdCachingFailed), this);
    PCPokktManager::setAdEventListener(AD_DISPLAYED_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdDisplayed), this);
    PCPokktManager::setAdEventListener(AD_SKIPPED_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdSkipped), this);
    PCPokktManager::setAdEventListener(AD_COMPLETED_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdCompleted), this);
    PCPokktManager::setAdEventListener(AD_CLOSED_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdClosed), this);
    PCPokktManager::setAdEventListener(AD_GRATIFIED_EVENT, PC_AD_EVENT_SELECTOR(AdDemoView::handleAdGratified), this);
    
    return true;
}

AdDemoView::~AdDemoView()
{
    PCPokktManager::removeAdEventListener(AD_AVAILABILITY_EVENT);
    PCPokktManager::removeAdEventListener(AD_CACHING_COMPLETED_EVENT);
    PCPokktManager::removeAdEventListener(AD_CACHING_FAILED_EVENT);
    PCPokktManager::removeAdEventListener(AD_DISPLAYED_EVENT);
    PCPokktManager::removeAdEventListener(AD_SKIPPED_EVENT);
    PCPokktManager::removeAdEventListener(AD_COMPLETED_EVENT);
    PCPokktManager::removeAdEventListener(AD_CLOSED_EVENT);
    PCPokktManager::removeAdEventListener(AD_GRATIFIED_EVENT);
}

void AdDemoView::handleBackPress(Ref *pSender)
{
    ChangeViewParams params;
    params.viewToChange = DemoSelectorView;
    changeView(params);
	POKKTLOG("AdDemoView handlebackpress");
}

void AdDemoView::setAdConfig(PCAdConfig* adConfig)
{
    _adConfig = adConfig;
    _txtScreenName->setString(adConfig->screenName);
}

AdDemoView* AdDemoView::getView(std::string screenName)
{
    if (screenName.compare("DemoScreen1") == 0)
    {
        if (viewInstance1 == NULL)
        {
            viewInstance1 = AdDemoView::create();
            viewInstance1->retain();
        }
        return viewInstance1;
    }
    
    if (screenName.compare("DemoScreen2") == 0)
    {
        if (viewInstance2 == NULL)
        {
            viewInstance2 = AdDemoView::create();
            viewInstance2->retain();
        }
        return viewInstance2;
    }
    
    return NULL;
}


void AdDemoView::handleCacheVideoAd(Ref *pSender)
{
    _btnCacheVideoAd->setEnabled(false);
    _btnShowVideoAd->setEnabled(false);
    _btnCacheVideoAd->setTitleText("video ad is downloading...");
    _btnShowVideoAd->setTitleText("video ad is downloading...");
    
    // request pokkt-sdk for a rewarded ad to be cached
    _adConfig->adFormat = VIDEO;
    PCPokktManager::cacheAd(_adConfig);
}

void AdDemoView::handleShowVideoAd(Ref *pSender)
{
    CCLOG("checking for any available rewarded-ad...");
    _adConfig->adFormat = VIDEO;
    PCPokktManager::checkAdAvailability(_adConfig);
}

void AdDemoView::handleCacheInterstitialAd(Ref *pSender)
{
    _btnCacheInterstitialAd->setEnabled(false);
    _btnShowInterstitialAd->setEnabled(false);
    _btnCacheInterstitialAd->setTitleText("interstitial ad is downloading...");
    _btnShowInterstitialAd->setTitleText("interstitial ad is downloading...");
    
    // request pokkt-sdk for a non-rewarded ad to be cached
    _adConfig->adFormat = INTERSTITIAL;
    PCPokktManager::cacheAd(_adConfig);
}

void AdDemoView::handleShowInterstitialAd(Ref *pSender)
{
    // request pokkt-sdk to show a non-rewarded ad
    _adConfig->adFormat = INTERSTITIAL;
    PCPokktManager::showAd(_adConfig);
}

void AdDemoView::handleExportLog(Ref* pSender)
{
    PCPokktManager::exportLog();
}

// pokkt handlers
void AdDemoView::handleAdAvailability(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // extract values
    bool isAvailable = extraValues[IS_AVAILABLE].compare("true") == 0;
    
    CCLOG("[POKKT-CPP] %s %s ad for %s is %s!", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                                (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                                adConfig->screenName.c_str(),
                                                (isAvailable ? "available!" : "not available!"));
    
    _txtStatus->setString(isAvailable ? "ad available!" : "no ads available");
    
    PCPokktManager::showAd(adConfig);
}

void AdDemoView::handleAdCachingCompleted(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // extract values
    float vc = 0.0f;
    std::stringstream(extraValues[AD_VC]) >> vc;
    
    CCLOG("%s %s ad is cached for %s, associated vc is %f", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                                            (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                                            adConfig->screenName.c_str(),
                                                            vc);
    
    _txtStatus->setString("ad cached!");
    
    POKKTLOG("adConfig->isRewarded: %d", adConfig->isRewarded);
    
    if (adConfig->adFormat == VIDEO)
    {
        _btnCacheVideoAd->setTitleText("Video ad is cached!");
        _btnShowVideoAd->setTitleText("Show Video Ad (Cached)");
        _btnShowVideoAd->setEnabled(true);
    }
    else if(adConfig->adFormat == INTERSTITIAL)
    {
        _btnCacheInterstitialAd->setTitleText("Interstitial ad is cached!");
        _btnShowInterstitialAd->setTitleText("Show interstitial Ad (Cached)");
        _btnShowInterstitialAd->setEnabled(true);
    }
}

void AdDemoView::handleAdCachingFailed(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // extract values
    std::string message = extraValues[FAIL_MESSAGE];
    
    CCLOG("%s %s ad caching failed for %s! message: %s", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                                         (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                                         adConfig->screenName.c_str(),
                                                         message.c_str());
    
    _txtStatus->setString("ad caching failed!");
    
    if (adConfig->adFormat == VIDEO)
    {
        _btnCacheVideoAd->setTitleText("Cache Video Ad");
        _btnShowVideoAd->setTitleText("Show Video Ad");
        _btnCacheVideoAd->setEnabled(true);
        _btnShowVideoAd->setEnabled(true);
    }
    else if(adConfig->adFormat == INTERSTITIAL)
    {
        _btnCacheInterstitialAd->setTitleText("Cache Interstial Ad");
        _btnShowInterstitialAd->setTitleText("Show Interstial Ad");
        _btnCacheInterstitialAd->setEnabled(true);
        _btnShowInterstitialAd->setEnabled(true);
    }
}

void AdDemoView::handleAdDisplayed(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // ignore extraValue param
    
    CCLOG("%s %s ad is displayed for %s!", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                           (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                           adConfig->screenName.c_str());
    
    _txtStatus->setString("ad displayed!");
    
    if (adConfig->adFormat == VIDEO)
    {
        _btnCacheVideoAd->setEnabled(false);
        _btnShowVideoAd->setEnabled(false);
    }
    else if(adConfig->adFormat == INTERSTITIAL)
    {
        _btnCacheInterstitialAd->setEnabled(false);
        _btnShowInterstitialAd->setEnabled(false);
    }
}

void AdDemoView::handleAdSkipped(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // ignore extraValue param
    
    CCLOG("%s %s ad is skipped for %s!", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                         (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                         adConfig->screenName.c_str());
    
    _txtStatus->setString("ad skipped!");
}

void AdDemoView::handleAdCompleted(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // ignore extraValue param
    
    CCLOG("%s %s ad is completed for %s!", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                           (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                           adConfig->screenName.c_str());
    
    _txtStatus->setString("ad completed!");
}

void AdDemoView::handleAdClosed(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // extract values
    bool backPressed = extraValues[BACK_PRESSED].compare("true") == 0;
    
    CCLOG("%s %s ad is closed for %s!", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                        (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                        adConfig->screenName.c_str());
    
    if (adConfig->adFormat == VIDEO)
    {
        _btnCacheVideoAd->setEnabled(true);
        _btnShowVideoAd->setEnabled(true);
        _btnCacheVideoAd->setTitleText("Cache Video Ad");
        _btnShowVideoAd->setTitleText("Show Video Ad");
    }
    else
    {
        _btnCacheInterstitialAd->setEnabled(true);
        _btnShowInterstitialAd->setEnabled(true);
        _btnCacheInterstitialAd->setTitleText("Cache Non-Rewarded Ad");
        _btnShowInterstitialAd->setTitleText("Show Non-Rewarded Ad");
    }
}

void AdDemoView::handleAdGratified(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues)
{
    if (adConfig->screenName != _adConfig->screenName)
        return;
    
    // extract values
    float reward = 0;
    std::stringstream(extraValues[REWARD]) >> reward;
    
    CCLOG("ad for %s %s is gratified! reward received: %f!", (adConfig->isRewarded ? "rewarded" : "non-rewarded"),
                                                             (adConfig->adFormat == VIDEO ? "video" : "interstitial"),
                                                             reward);

    _coinsEarned += reward;
    
    char buf[100];
    sprintf(buf, "Points Earned: %f", _coinsEarned);
    _txtPointsEarned->setString(buf);
}
