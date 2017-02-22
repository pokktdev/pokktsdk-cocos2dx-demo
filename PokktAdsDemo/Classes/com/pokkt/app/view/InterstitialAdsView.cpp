#include "InterstitialAdsView.h"


static InterstitialAdsView* viewInstance1 = NULL;

InterstitialAdsView::~InterstitialAdsView()
{
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_CACHING_COMPLETED);
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_CACHING_FAILED);
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_DISPLAYED);
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_CLOSED);
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_SKIPPED);
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_COMPLETED);
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_GRATIFIED);
    PCPokktAds::removeAdEventListener(EVENT_INTERSTITIAL_AVAILABILITY);

}

bool InterstitialAdsView::init()
{
    if (!BaseView::init())
        return false;
    
    _coinsEarned = 0;
    
    logo->setPosition(logo->getPosition().x, logo->getPosition().y + 100);
    
    int yPos = logo->getPosition().y - logo->getBoundingBox().size.height / 2;
    
    _screenNameEditBox = EditBox::create(Size(3 * visibleSize.width / 4, 70), "whiteButton.png");
    _screenNameEditBox->setPlaceHolder("start");
    _screenNameEditBox->setFontColor(Color3B::BLACK);
    _screenNameEditBox->setPosition((Vec2(visibleSize.width / 2, yPos)));
    _screenNameEditBox->setFontSize(35);
    _screenNameEditBox->setInputMode(EditBox::InputMode::ANY);
    _screenNameEditBox->setDelegate(this);
    _screenNameEditBox->setReturnType(EditBox::KeyboardReturnType::DONE);
    addChild(_screenNameEditBox);
    
    // create new UI
    
    yPos -= 100;
    
    _btnCacheRewardedInterstitialAd = createButton("Cache Rewarded Ad", CC_CALLBACK_1(InterstitialAdsView::handleCacheRewardedInterstitialAd, this));
    
    _btnCacheRewardedInterstitialAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnCacheRewardedInterstitialAd);
    
    yPos -= 100;
    
    _btnShowRewardedInterstitialAd = createButton("Show Ad", CC_CALLBACK_1(InterstitialAdsView::handleShowRewardedInterstitialAd, this));
    _btnShowRewardedInterstitialAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnShowRewardedInterstitialAd);
    
    yPos -= 100;
    
    _btnCacheNonRewardedInterstitialAd = createButton("Cache Non Rewarded Ad", CC_CALLBACK_1(InterstitialAdsView::handleCacheNonRewardedInterstitialAd, this));
    _btnCacheNonRewardedInterstitialAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnCacheNonRewardedInterstitialAd);
    
    yPos -= 100;
    
    _btnShowNonRewardedInterstitialAd = createButton("Show Non Rewarded Ad", CC_CALLBACK_1(InterstitialAdsView::handleShowNonRewardedInterstitialAd, this));
    _btnShowNonRewardedInterstitialAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnShowNonRewardedInterstitialAd);
    
    ///////
    yPos -= 420;
    _txtPointsEarned = BaseView::createLabel("Earned Points: 0", 35, Color3B::BLACK, Vec2(visibleSize.width / 2, yPos));
    _txtPointsEarned->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtPointsEarned);
    
    yPos -= 100;
    
    _txtStatus = createLabel("", 35, Color3B::BLACK, Vec2(visibleSize.width / 2, yPos));
    _txtStatus->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtStatus);
    
    
    ///////
    
    
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_AVAILABILITY, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdAvailability), this);
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_CACHING_COMPLETED, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdCachingCompleted), this);
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_CACHING_FAILED, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdCachingFailed), this);
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_DISPLAYED, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdDisplayed), this);
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_SKIPPED, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdSkipped), this);
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_COMPLETED, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdCompleted), this);
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_CLOSED, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdClosed), this);
    PCPokktAds::setAdEventListener(EVENT_INTERSTITIAL_GRATIFIED, PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdGratified), this);
    
    return true;
}

void InterstitialAdsView::handleCacheRewardedInterstitialAd(Ref* pSender)
{
    PCPokktAds::cacheRewardedInterstitialAd(_screenNameEditBox->getText());
}

void InterstitialAdsView::handleShowRewardedInterstitialAd(Ref* pSender)
{
    PCPokktAds::showRewardedInterstitialAd(_screenNameEditBox->getText());
}

void InterstitialAdsView::handleCacheNonRewardedInterstitialAd(Ref* pSender)
{
    PCPokktAds::cacheNonRewardedInterstitialAd(_screenNameEditBox->getText());
}

void InterstitialAdsView::handleShowNonRewardedInterstitialAd(Ref* pSender)
{
    PCPokktAds::showNonRewardedInterstitialAd(_screenNameEditBox->getText());
}

/// handler methods

void InterstitialAdsView::handleAdAvailability(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdAvailability");
    CCLOG("%s Interstitial ad is cached for Interstitial %s, associated vc is %s", (isAvailable ? "rewarded" : "non-rewarded"),screenName.c_str(),
          args.c_str());
    
    _txtStatus->setString(isAvailable ? "ad available!" : "no ads available");
}

void InterstitialAdsView::handleAdCachingCompleted(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdCachingCompleted");
    CCLOG("%s",args.c_str());
    _txtStatus->setString(isAvailable ? "Rewarded ad Cached!" : "Non Rewarded ad Cached!");
}

void InterstitialAdsView::handleAdCachingFailed(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdCachingFailed");
    _txtStatus->setString(isAvailable ? "Rewarded ad Cached failed!" : "Non Rewarded ad failed!");
}

void InterstitialAdsView::handleAdDisplayed(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdDisplayed");
    _txtStatus->setString("Ad Displayed");
}

void InterstitialAdsView::handleAdSkipped(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdSkipped");
    _txtStatus->setString("Ad Skipped");
}

void InterstitialAdsView::handleAdCompleted(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdCompleted");
    _txtStatus->setString("Ad Completed");
}

void InterstitialAdsView::handleAdClosed(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdClosed");
    _txtStatus->setString("Ad Closed");
}

void InterstitialAdsView::handleAdGratified(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdGratified");
    
    char buf[100];
    float temp = ::atof(args.c_str());
    _coinsEarned = _coinsEarned + temp;
    sprintf(buf, "Earned Points: %s", args.c_str());
    _txtPointsEarned->setString(buf);
}





void InterstitialAdsView::handleBackPress(Ref *pSender)
{
    ChangeViewParams params;
    params.viewToChange = DemoSelectorView;
    changeView(params);
    POKKTLOG("VideoAdsView handlebackpress");
}

InterstitialAdsView* InterstitialAdsView::getView(std::string screenName)
{
    if (viewInstance1 == NULL)
    {
        viewInstance1 = InterstitialAdsView::create();
        viewInstance1->retain();
    }
    
    return viewInstance1;
}

void InterstitialAdsView::editBoxEditingDidBegin(EditBox* editBox)
{
    _screenNameEditBox->attachWithIME();
}

void InterstitialAdsView::editBoxEditingDidEnd(EditBox* editBox)
{
    
}

void InterstitialAdsView::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}

void InterstitialAdsView::editBoxReturn(EditBox* editBox)
{
    
}

