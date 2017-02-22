#include "OfferwallView.h"
#include "DemoSelectorView.h"


static OfferwallView* viewInstance = NULL;

bool OfferwallView::init()
{
    if (!BaseView::init())
        return false;
    
    _coinsEarned = 0;
    
    logo->setPosition(logo->getPosition().x, logo->getPosition().y + 100);
    
    int yPos = logo->getPosition().y - logo->getBoundingBox().size.height / 2;
    
    
    auto lblPointEarned = BaseView::createLabel("Points Earned: ", 35, Color3B::BLACK, Vec2(visibleSize.width / 2 - 30, yPos));
    lblPointEarned->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    this->addChild(lblPointEarned);
    
    _txtPointsEarned = BaseView::createLabel("0", 35, Color3B::BLACK,
                                             Vec2(lblPointEarned->getBoundingBox().size.width / 2 + lblPointEarned->getPosition().x + 20, yPos));
    this->addChild(_txtPointsEarned);
    
    yPos -= 100;
    
    _btnGetOfferwallAny = createButton("Get Offerwall (Any Asset Value)", CC_CALLBACK_1(OfferwallView::handleGetOfferwallAny, this));
    _btnGetOfferwallAny->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnGetOfferwallAny);
    
    yPos -= 100;
    
    _txiEnterMaxPoints = TextField::create();
    _txiEnterMaxPoints->setPlaceHolder("Enter Max Points");
    _txiEnterMaxPoints->setPlaceHolderColor(Color3B::GRAY);
    _txiEnterMaxPoints->ignoreContentAdaptWithSize(false);
    _txiEnterMaxPoints->setFontSize(30);
    _txiEnterMaxPoints->setPosition(Vec2(visibleSize.width / 2, yPos));
    _txiEnterMaxPoints->setSize(Size(500, 50));
    _txiEnterMaxPoints->setTextHorizontalAlignment(TextHAlignment::CENTER);
    this->addChild(_txiEnterMaxPoints);
    
    yPos -= 80;
    
    _btnGetOfferwallFix = createButton("Get Offerwall (Fix asset value)", CC_CALLBACK_1(OfferwallView::handleGetOfferwallFix, this), "button_purple.png");
    _btnGetOfferwallFix->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnGetOfferwallFix);
    
    yPos -= 100;
    
    _btnIncompleteCallback = createButton("Incomplete callback", CC_CALLBACK_1(OfferwallView::handleIncompleteCallback, this));
    _btnIncompleteCallback->setPosition(Vec2(visibleSize.width / 2, yPos));
    this->addChild(_btnIncompleteCallback);
    
    yPos -= 120;
    
    _btnExportLog = createButton("Export Log", CC_CALLBACK_1(OfferwallView::handleExportLog, this));
    _btnExportLog->setPosition(Vec2(visibleSize.width / 2, yPos));
    _btnExportLog->setScale(0.7f);
    this->addChild(_btnExportLog);
    
    yPos -= 100;
    
    // pokkt init for offerwall
    PCPokktManager::checkOfferwallCampaign();
    PCPokktManager::getPendingCoins();
    
    // listen for pokkt events
    PCPokktManager::setOfferwallEventListener(COIN_RESPONSE_EVENT, PC_OFFERWALL_EVENT_SELECTOR(OfferwallView::handleCoinResponse), this);
    PCPokktManager::setOfferwallEventListener(COIN_RESPONSE_WITH_TRANS_ID_EVENT, PC_OFFERWALL_EVENT_SELECTOR(OfferwallView::handleCoinResponseWithTrId), this);
    PCPokktManager::setOfferwallEventListener(COIN_RESPONSE_FAILED_EVENT, PC_OFFERWALL_EVENT_SELECTOR(OfferwallView::handleCoinResponseFailed), this);
    PCPokktManager::setOfferwallEventListener(CAMPAIGN_AVAILABILITY_EVENT, PC_OFFERWALL_EVENT_SELECTOR(OfferwallView::handleCampaignAvailibity), this);
    PCPokktManager::setOfferwallEventListener(OFFERWALL_CLOSED_EVENT, PC_OFFERWALL_EVENT_SELECTOR(OfferwallView::handleOfferwallclosed), this);
    
    return true;
}

OfferwallView::~OfferwallView()
{
    PCPokktManager::removeOfferwallEventListener(COIN_RESPONSE_EVENT);
    PCPokktManager::removeOfferwallEventListener(COIN_RESPONSE_WITH_TRANS_ID_EVENT);
    PCPokktManager::removeOfferwallEventListener(COIN_RESPONSE_FAILED_EVENT);
    PCPokktManager::removeOfferwallEventListener(CAMPAIGN_AVAILABILITY_EVENT);
    PCPokktManager::removeOfferwallEventListener(OFFERWALL_CLOSED_EVENT);
}

OfferwallView* OfferwallView::getView()
{
    if (viewInstance == NULL)
    {
        viewInstance = OfferwallView::create();
        viewInstance->retain();
    }
    return viewInstance;
}

void OfferwallView::handleBackPress(Ref *pSender)
{
    ChangeViewParams params;
    params.viewToChange = DemoSelectorView;
    changeView(params);
}

void OfferwallView::handleEnterForeground()
{
    PCPokktManager::getPendingCoins();
}

void OfferwallView::handleGetOfferwallAny(Ref *pSender)
{
    PCPokktConfig* config = DemoSelectorView::getPokktConfig();
    config->offerwallAssetValue = "";
    PCPokktManager::getCoins(config);
}

void OfferwallView::handleGetOfferwallFix(Ref *pSender)
{
    PCPokktConfig* config = DemoSelectorView::getPokktConfig();
    config->offerwallAssetValue = _txiEnterMaxPoints->getString();
    PCPokktManager::getCoins(config);
}

void OfferwallView::handleIncompleteCallback(Ref *pSender)
{
    PCPokktManager::getPendingCoins();
}

void OfferwallView::handleExportLog(Ref* pSender)
{
    PCPokktManager::exportLog();
}

void OfferwallView::handleCoinResponse(std::string coins)
{
    CCLOG("[POKKT-CPP] Coins earned from offerwall: %s", coins.c_str());
    
    int coinsInt = 0;
    std::stringstream(coins) >> coinsInt;
    _coinsEarned += coinsInt;
    
    char buf[100];
    sprintf(buf, "%d", _coinsEarned);
    _txtPointsEarned->setString(buf);
    
    // if auto-close is enables, close this screen
    //if (_chkCloseOnSuccess->isSelected())
    //    handleBackPress();
}

void OfferwallView::handleCoinResponseWithTrId(std::string coinsWithTrId)
{
    // extract comma separated values
    std::stringstream stream(coinsWithTrId);
    std::string value;
    std::vector<std::string> values;
    while (getline(stream, value, ','))
    {
        values.push_back(value);
        if (stream.peek() == ',')
            stream.ignore();
    }
    
    if (values.size() < 2)
        return; // the values received are not proper
    
    std::string points = values[0];
    std::string transId = values[1];
    
    if (points == "-1")
    {
        // no points earned
    }
    else
    {
        // points earned equal to coins with transaction id
    }
    
    
    if (values.size() >= 2)
        CCLOG("[POKKT-CPP] Coins earned with trId: %s, coins: %s.", values[1].c_str(), values[0].c_str());
    else
        CCLOG("[POKKT-CPP] Error receiving coins with transaction id!");
    
    _txtPointsEarned->setString(coinsWithTrId.c_str());
    
    // if auto-close is enables, close this screen
    //if (_chkCloseOnSuccess->isSelected())
    //    handleBackPress(NULL);
}

void OfferwallView::handleCoinResponseFailed(std::string message)
{
    // pending coins request fails
    CCLOG("[POKKT-CPP] Failed to get Pending coins!");
}

void OfferwallView::handleCampaignAvailibity(std::string message)
{
    bool available = message == "true";
    
    CCLOG("[POKKT-CPP] Offerwall Campaign availability: %s", (available ? "available" : "no campaigns"));
}

void OfferwallView::handleOfferwallclosed(std::string message)
{
    CCLOG("[POKKT-CPP] Offerwall Closed!");
}
