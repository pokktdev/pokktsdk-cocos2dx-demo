
#include "BannerAdsView.h"

static BannerAdsView* viewInstance1 = NULL;

BannerAdsView::~BannerAdsView()
{
    PCPokktAds::removeAdEventListener(EVENT_BANNER_LOADED_OP);
    PCPokktAds::removeAdEventListener(EVENT_BANNER_LOAD_FAILED_OP);
}

bool BannerAdsView::init()
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
    
    _btnLoadTopBannerAd = createButton("Load Top Banner", CC_CALLBACK_1(::BannerAdsView::handleLoadTopBannerAd, this));
    
    _btnLoadTopBannerAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnLoadTopBannerAd);
    
    yPos -= 100;
    
    _btnDestroyTopBannerAd = createButton("Destroy Banner", CC_CALLBACK_1(BannerAdsView::handleDestroyTopBannerAd, this));
    _btnDestroyTopBannerAd->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnDestroyTopBannerAd);
    
    yPos -= 100;
    
    _txtStatus = createLabel("", 35, Color3B::BLACK, Vec2(visibleSize.width / 2, yPos));
    _txtStatus->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txtStatus);
    
    ///////
    
    PCPokktAds::setAdEventListener(EVENT_BANNER_LOADED_OP, PC_ADS_EVENT_SELECTOR(BannerAdsView::handleBannerLoadSuccessfuly), this);
    PCPokktAds::setAdEventListener(EVENT_BANNER_LOAD_FAILED_OP, PC_ADS_EVENT_SELECTOR(BannerAdsView::handleBannerLoadFailed), this);
    
    return true;
}

void BannerAdsView::handleLoadTopBannerAd(Ref* pSender)
{
    PCPokktAds::loadBannerWithRect(_screenNameEditBox->getText(),320, 50, 0, 0);
    PCPokktAds::setBannerAutoRefresh("1");
}


void BannerAdsView::handleDestroyTopBannerAd(Ref* pSender)
{
    PCPokktAds::destroyBanner();
}

void BannerAdsView::handleBannerLoadSuccessfuly(std::string screenName, bool isAvailable, std::string args)
{
    char buf[300];
    sprintf(buf, "Banner Loaded %s", screenName.c_str());
    _txtStatus->setString(buf);
}

void BannerAdsView::handleBannerLoadFailed(std::string screenName, bool isAvailable, std::string args)
{
    char buf[300];
    sprintf(buf, "Banner Loaded failed %s", screenName.c_str());
    _txtStatus->setString(buf);
}





void BannerAdsView::handleBackPress(Ref *pSender)
{
    PCPokktAds::destroyBanner();
    ChangeViewParams params;
    params.viewToChange = DemoSelectorView;
    changeView(params);
    POKKTLOG("VideoAdsView handlebackpress");
}

BannerAdsView* BannerAdsView::getView(std::string screenName)
{
    if (viewInstance1 == NULL)
    {
        viewInstance1 = BannerAdsView::create();
        viewInstance1->retain();
    }
    
    return viewInstance1;
}

void BannerAdsView::editBoxEditingDidBegin(EditBox* editBox)
{
    _screenNameEditBox->attachWithIME();
}

void BannerAdsView::editBoxEditingDidEnd(EditBox* editBox)
{
    
}

void BannerAdsView::editBoxTextChanged(EditBox* editBox, const std::string& text)
{
    
}

void BannerAdsView::editBoxReturn(EditBox* editBox)
{
    
}

