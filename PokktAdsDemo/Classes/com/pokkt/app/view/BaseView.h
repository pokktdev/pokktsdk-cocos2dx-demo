#ifndef __CocosPokktApp__BaseView__
#define __CocosPokktApp__BaseView__

#include <stdio.h>
#include "cocos2d.h"
#include "../../../../../cocos2d/cocos/ui/UIButton.h"
#include "../../../../../cocos2d/cocos/ui/UIText.h"
#include "../../../../pokktsdk/pokkt.h"


class BaseView : public cocos2d::Layer
{
public:
    enum AppView
    {
        AdDemoView,
        DemoSelectorView,
        VideoAdsView,
        InterstitialAdsView,
        BannerAdsView
    };
    
    typedef struct __changeViewParams
    {
        AppView viewToChange;
    } ChangeViewParams;
    
    CREATE_FUNC(BaseView);
    
    virtual ~BaseView();
    
    void update(float dt);
    virtual void handleBackPress(cocos2d::Ref* pSender);
    virtual void handleEnterForeground();
    
    virtual void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event);
    
    static cocos2d::ui::Button* createButton(const std::string &label,
                                             const cocos2d::ui::Button::ccWidgetClickCallback &callback,
                                             const std::string &imageName = "button_blue.png",
                                             int width = 500, int height = 80, int fontSize = 28);
    
    static cocos2d::ui::Text* createLabel(const std::string &label, int fontSize = 20,
                                          const cocos2d::Color3B &color = cocos2d::Color3B::WHITE,
                                          const cocos2d::Vec2 &position = cocos2d::Vec2(0, 0));
    
protected:
    
    cocos2d::Sprite* logo;
    cocos2d::ui::Button* backButton;
    cocos2d::Size visibleSize;
    
    virtual bool init();
    void changeView(ChangeViewParams params);
    void changeLabelText(cocos2d::ui::Text* label, std::string text);
    //void changeButtonLabel(cocos2d::ui::Button* button, std::string text);
    
private:
    
    std::map<cocos2d::ui::Text*, std::string> _labelsToUpdate;
};

#endif /* defined(__CocosPokktApp__BaseView__) */
