#include "VideoAdsView.h"


static VideoAdsView* viewInstance1 = NULL;

 VideoAdsView::~VideoAdsView()
{
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_CACHING_COMPLETED);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_CACHING_FAILED);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_DISPLAYED);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_FAILED_TO_SHOW);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_CLOSED);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_SKIPPED);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_COMPLETED);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_GRATIFIED);
    PCPokktAds::removeAdEventListener(EVENT_VIDEO_AD_AVAILABILITY);
}

bool VideoAdsView::init()
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
    
    
    yPos -= 120;

    
    _btnCacheRewardedVideoAd = createButton("Cache Rewarded Ad", CC_CALLBACK_1(VideoAdsView::handleCacheRewardedVideoAd, this));
    
    _btnCacheRewardedVideoAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnCacheRewardedVideoAd);
    
    yPos -= 100;
    
    _btnShowRewardedVideoAd = createButton("Show Ad", CC_CALLBACK_1(VideoAdsView::handleShowRewardedVideoAd, this));
    _btnShowRewardedVideoAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnShowRewardedVideoAd);
    
    yPos -= 100;
    
    _btnCacheNonRewardedVideoAd = createButton("Cache Non Rewarded Ad", CC_CALLBACK_1(VideoAdsView::handleCacheNonRewardedVideoAd, this));
    _btnCacheNonRewardedVideoAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnCacheNonRewardedVideoAd);
    
    yPos -= 100;
    
    _btnShowNonRewardedVideoAd = createButton("Show Non Rewarded Ad", CC_CALLBACK_1(VideoAdsView::handleShowNonRewardedVideoAd, this));
    _btnShowNonRewardedVideoAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnShowNonRewardedVideoAd);
    
    yPos -= 420;
    
    _txtPointsEarned = BaseView::createLabel("Earned Points: 0", 35, Color3B::BLACK, Vec2(visibleSize.width / 2, yPos));
    _txtPointsEarned->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtPointsEarned);
    
     yPos -= 100;
    
    _txtStatus = createLabel("", 35, Color3B::BLACK, Vec2(visibleSize.width / 2, yPos));
    _txtStatus->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtStatus);

    ///////
    
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_AVAILABILITY, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdAvailability), this);
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_CACHING_COMPLETED, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdCachingCompleted), this);
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_CACHING_FAILED, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdCachingFailed), this);
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_DISPLAYED, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdDisplayed), this);
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_SKIPPED, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdSkipped), this);
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_COMPLETED, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdCompleted), this);
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_CLOSED, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdClosed), this);
    PCPokktAds::setAdEventListener(EVENT_VIDEO_AD_GRATIFIED, PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdGratified), this);
    
    return true;
}

void VideoAdsView::handleCacheRewardedVideoAd(Ref* pSender)
{
    PCPokktAds::cacheRewardedVideoAd(_screenNameEditBox->getText());
}

void VideoAdsView::handleShowRewardedVideoAd(Ref* pSender)
{
    PCPokktAds::showRewardedVideoAd(_screenNameEditBox->getText());
}

void VideoAdsView::handleCacheNonRewardedVideoAd(Ref* pSender)
{
    PCPokktAds::cacheNonRewardedVideoAd(_screenNameEditBox->getText());
}

void VideoAdsView::handleShowNonRewardedVideoAd(Ref* pSender)
{
    PCPokktAds::showNonRewardedVideoAd(_screenNameEditBox->getText());
}

/// handler methods

void VideoAdsView::handleAdAvailability(std::string screenName, bool isAvailable, std::string args)
{
    CCLOG("handleAdAvailability");
    CCLOG("%s video ad is cached for video %s, associated vc is %s", (isAvailable ? "rewarded" : "non-rewarded"),screenName.c_str(),
          args.c_str());
    
    _txtStatus->setString(isAvailable ? "ad available!" : "no ads available");
}

void VideoAdsView::handleAdCachingCompleted(std::string screenName, bool isAvailable, std::string args)
{
     CCLOG("handleAdCachingCompleted");
    _txtStatus->setString(isAvailable ? "Rewarded ad Cached!" : "Non Rewarded ad Cached!");
}

void VideoAdsView::handleAdCachingFailed(std::string screenName, bool isAvailable, std::string args)
{
     CCLOG("handleAdCachingFailed");
     _txtStatus->setString(isAvailable ? "Rewarded ad Cached failed!" : "Non Rewarded ad failed!");
}

void VideoAdsView::handleAdDisplayed(std::string screenName, bool isAvailable, std::string args)
{
     CCLOG("handleAdDisplayed");
    _txtStatus->setString("Ad Displayed");
}

void VideoAdsView::handleAdSkipped(std::string screenName, bool isAvailable, std::string args)
{
     CCLOG("handleAdSkipped");
    _txtStatus->setString("Ad Skipped");
}

void VideoAdsView::handleAdCompleted(std::string screenName, bool isAvailable, std::string args)
{
     CCLOG("handleAdCompleted");
     _txtStatus->setString("Ad Completed");
}

void VideoAdsView::handleAdClosed(std::string screenName, bool isAvailable, std::string args)
{
     CCLOG("handleAdClosed");
    _txtStatus->setString("Ad Closed");
}

void VideoAdsView::handleAdGratified(std::string screenName, bool isAvailable, std::string args)
{
     CCLOG("handleAdGratified");
    
    char buf[100];
    float temp = ::atof(args.c_str());
    _coinsEarned = _coinsEarned + temp;
    sprintf(buf, "Earned Points: %s", args.c_str());
    _txtPointsEarned->setString(buf);
}


void VideoAdsView::handleBackPress(Ref *pSender)
{
    ChangeViewParams params;
    params.viewToChange = DemoSelectorView;
    changeView(params);
    POKKTLOG("VideoAdsView handlebackpress");
}

VideoAdsView* VideoAdsView::getView(std::string screenName)
{
    if (viewInstance1 == NULL)
    {
        viewInstance1 = VideoAdsView::create();
        viewInstance1->retain();
    }
    
    return viewInstance1;
}

void VideoAdsView::editBoxEditingDidBegin(EditBox* editBox)
{
    _screenNameEditBox->attachWithIME();
}

void VideoAdsView::editBoxEditingDidEnd(EditBox* editBox)
{
    
}

void VideoAdsView::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}

void VideoAdsView::editBoxReturn(EditBox* editBox)
{
    
}


