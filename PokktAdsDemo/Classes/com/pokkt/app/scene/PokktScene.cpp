#include "PokktScene.h"
#include "../../../../../cocos2d/cocos/ui/UIButton.h"
//#include "../view/OfferwallView.h"
#include "../view/VideoAdsView.h"
#include "../view/InterstitialAdsView.h"
#include "../view/BannerAdsView.h"
#include "../view/DemoSelectorView.h"
#include <stdlib.h>

USING_NS_CC;


Scene* PokktScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PokktScene::create();
    layer->setName("sceneLayer");

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void PokktScene::handleEnterForeground()
{
    _currentView->handleEnterForeground();
}

// on "init" you need to initialize your instance
bool PokktScene::init()
{
    if (!LayerColor::initWithColor(Color4B(cocos2d::Color3B::WHITE)))
        return false;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // listen for screen/view change events
    _eventDispatcher->addCustomEventListener("changeView", CC_CALLBACK_1(PokktScene::handleChangeScene, this));
    
    // default view
    auto view = BaseView::AppView::DemoSelectorView;
    _eventDispatcher->dispatchCustomEvent("changeView", &view);
    
    // add a close button
    auto closeButton = BaseView::createButton("", CC_CALLBACK_1(PokktScene::handleCloseCallback, this), "CloseNormal.png");
    closeButton->setScale9Enabled(false);
	closeButton->setPosition(Vec2(visibleSize.width - closeButton->getContentSize().width / 2, closeButton->getContentSize().height / 2));
    this->addChild(closeButton);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    closeButton->setVisible(false);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    closeButton->setVisible(true);
#endif
    
    // version
   // initVersion(PCPokktManager::getSDKVersion());
    
    return true;
}

void PokktScene::onKeyRelease(EventKeyboard::KeyCode keyCode, Event *event)
{
    LayerColor::onKeyReleased(keyCode, event);
    
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        if (_currentView != NULL)
            _currentView->handleBackPress(NULL);
    }
}

void PokktScene::initVersion(const std::string &version)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Text* txtVersion = BaseView::createLabel(version, 20, Color3B::BLACK);
    txtVersion->setPosition(Vec2(visibleSize.width - txtVersion->getBoundingBox().size.width, visibleSize.height - txtVersion->getBoundingBox().size.height));
    this->addChild(txtVersion);
}

void PokktScene::handleChangeScene(Ref *pSender)
{
	POKKTLOG("PokktScene handleChangeScene");
    auto event = static_cast<EventCustom*>(pSender);
    auto params = *static_cast<BaseView::ChangeViewParams*>(event->getUserData());
    
    // initiate view change
    if (_currentView != NULL)
    {
		_currentView->setKeyboardEnabled(false);
        this->removeChild(_currentView, false);
        _currentView = NULL;
    }
    
    switch (params.viewToChange)
    {
      //  case BaseView::AppView::OfferwallView:
           // _currentView = static_cast<OfferwallView*>(OfferwallView::getView());
       //     break;
            
        case BaseView::AppView::AdDemoView:
            break;
            
        case BaseView::AppView::DemoSelectorView:
            _currentView = static_cast<DemoSelectorView*>(DemoSelectorView::getView());
            break;
            
        case BaseView::AppView::VideoAdsView:
        {
            VideoAdsView* view = static_cast<VideoAdsView*>(VideoAdsView::create());
            //view->setAdConfig(params.adConfig);
            _currentView = view;
        }
            break;
            
        case BaseView::AppView::InterstitialAdsView:
        {
            InterstitialAdsView* view = static_cast<InterstitialAdsView*>(InterstitialAdsView::create());
            //view->setAdConfig(params.adConfig);
            _currentView = view;
        }
            break;
            
        case BaseView::AppView::BannerAdsView:
        {
            BannerAdsView* view = static_cast<BannerAdsView*>(BannerAdsView::create());
            _currentView = view;
        }
            break;

    }
    
	if (_currentView != NULL)
	{
		_currentView->setKeyboardEnabled(true);
		this->addChild(_currentView);
	}
}

void PokktScene::handleCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
