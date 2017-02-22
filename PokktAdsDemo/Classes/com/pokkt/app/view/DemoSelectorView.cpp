#include "DemoSelectorView.h"


/**
 * HELPER: getAdConfigForScreen
 *
 * this is just for this Demo-purpose, you should have
 * your own adConfig properly mainatined
 **/

static DemoSelectorView* viewInstance = NULL;

bool DemoSelectorView::init()
{
    if (!BaseView::init())
        return false;
    
    backButton->setVisible(false);
    
    int yPos = logo->getPosition().y - logo->getBoundingBox().size.height / 2;
    
    
    // create new UI
    
    _videoAds = createButton("Video Ads", CC_CALLBACK_1(DemoSelectorView::handleVideoAdsPokkt, this));
    
    _videoAds->setPosition(Vec2(visibleSize.width / 2, yPos));
    _videoAds->setScale(1.0f);
    this->addChild(_videoAds);
    
    yPos -= 100;
    
    _interstitialAds = createButton("Interstitial Ad", CC_CALLBACK_1(DemoSelectorView::handleInterstitialAdsPokkt, this));
    _interstitialAds->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_interstitialAds);
    
    yPos -= 100;
    
    _bannerAds = createButton("Banner Ad", CC_CALLBACK_1(DemoSelectorView::handleBannerAdsPokkt, this));
    _bannerAds->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_bannerAds);
    
    yPos -= 100;
    
    _btnExportLog = createButton("Export Log", CC_CALLBACK_1(DemoSelectorView::handleExportLog, this));
    _btnExportLog->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnExportLog);
    
    
    return true;
}

DemoSelectorView::~DemoSelectorView()
{
    
}


DemoSelectorView* DemoSelectorView::getView()
{
    if (viewInstance == NULL)
    {
        viewInstance = DemoSelectorView::create();
        viewInstance->retain();
    }
    return viewInstance;
}

void DemoSelectorView::handleBackPress(cocos2d::Ref *pSender)
{
    // exit the app
    Director::getInstance()->end();
}

void DemoSelectorView::handleVideoAdsPokkt(Ref* pSender)
{
    ChangeViewParams params;
    params.viewToChange = VideoAdsView;
    changeView(params);
}

void DemoSelectorView::handleInterstitialAdsPokkt(Ref* pSender)
{
    ChangeViewParams params;
    params.viewToChange = InterstitialAdsView;
    changeView(params);
}

void DemoSelectorView::handleBannerAdsPokkt(Ref* pSender)
{
    ChangeViewParams params;
    params.viewToChange = BannerAdsView;
    changeView(params);
}

void DemoSelectorView::handleExportLog(cocos2d::Ref* pSender)
{
    PCPokktAds::exportLog();
}


void DemoSelectorView::editBoxEditingDidBegin(EditBox* editBox)
{
    _screenNameEditBox->attachWithIME();
}

void DemoSelectorView::editBoxEditingDidEnd(EditBox* editBox)
{
    
}

void DemoSelectorView::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}

void DemoSelectorView::editBoxReturn(EditBox* editBox)
{
    
}
