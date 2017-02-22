#include "AppDelegate.h"
#include "../cocos2d/cocos/platform/CCGLView.h"
#include "com/pokkt/app/scene/PokktScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview)
    {
        glview = GLViewImpl::create("Pokkt App");
        director->setOpenGLView(glview);
    }
    glview->setDesignResolutionSize(750, 1334, ResolutionPolicy::FIXED_HEIGHT);
    //glview->setContentScaleFactor(0.5f);

    // create a scene. it's an autorelease object
    _scene = PokktScene::createScene();

    // run
    director->runWithScene(_scene);
    
    
    // set pokkt config
    std::string appId = "a2717a45b835b5e9f50284a38d62a74e";
    std::string securityKey = "iJ02lJss0M";
    
    PCPokktAds::shouldDebug(true);
    PCPokktAds::setPokktConfig(appId, securityKey);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();

    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();

    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    
    auto layer = _scene->getChildByName<PokktScene*>("sceneLayer");
    layer->handleEnterForeground();
}
