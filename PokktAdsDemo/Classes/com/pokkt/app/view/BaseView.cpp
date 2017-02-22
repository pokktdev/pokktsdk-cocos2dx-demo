#include "BaseView.h"


bool BaseView::init()
{
    if (!cocos2d::Node::init())
        return false;
    
    visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    
    // logo
    logo = cocos2d::Sprite::create("logo.png");
    logo->setPosition(visibleSize.width / 2, visibleSize.height - logo->getBoundingBox().size.height / 2);
    this->addChild(logo);
    
    backButton = createButton("", CC_CALLBACK_1(BaseView::handleBackPress, this), "back.png");
    backButton->setScale9Enabled(false);
    backButton->setScale(0.1f);
    backButton->setPosition(cocos2d::Vec2(backButton->getBoundingBox().size.width, backButton->getBoundingBox().size.height));
    this->addChild(backButton);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    backButton->setVisible(true);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    backButton->setVisible(true);
#endif
    
    // for back press detection
    setKeypadEnabled(true);
    
    this->scheduleUpdate();
    
    return true;
}

BaseView::~BaseView()
{
    // to override
}

void BaseView::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    Layer::onKeyReleased(keyCode, event);
    
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE || keyCode == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
    {
		POKKTLOG("BaseView handlebackpress");
        handleBackPress(NULL);
    }
}

void BaseView::changeView(ChangeViewParams params)
{
    _eventDispatcher->dispatchCustomEvent("changeView", &params);
}

void BaseView::changeLabelText(cocos2d::ui::Text* label, std::string text)
{
    _labelsToUpdate[label] = text;
}

//void BaseView::changeButtonLabel(cocos2d::ui::Button* button, std::string text)
//{
//    //CCLabelTTF* label = static_cast<CCLabelTTF*>(button->getChildByTag(341)); // because I know!
//    //button->la
//    //changeLabelText(label, text);
//}

void BaseView::update(float dt)
{
    std::map<cocos2d::ui::Text*, std::string>::iterator it = _labelsToUpdate.begin();
    for (; it != _labelsToUpdate.end(); ++it)
    {
        it->first->setString(it->second);
    }
    _labelsToUpdate.clear();
}

void BaseView::handleBackPress(cocos2d::Ref *pSender)
{
    // should override
}

void BaseView::handleEnterForeground()
{
    // should override
}

cocos2d::ui::Button* BaseView::createButton(const std::string &label,
                                            const cocos2d::ui::Button::ccWidgetClickCallback &callback,
                                            const std::string &imageName,
                                            int width, int height, int fontSize)
{
    auto button = cocos2d::ui::Button::create(imageName);
    button->setTitleFontSize(fontSize);
    button->setTitleText(label);
    button->setScale9Enabled(true);
    button->setSize(cocos2d::Size(width, height));
    button->addClickEventListener(callback);
    return button;
}

cocos2d::ui::Text* BaseView::createLabel(const std::string &label, int fontSize, const cocos2d::Color3B &color, const cocos2d::Vec2 &position)
{
    auto textLabel = cocos2d::ui::Text::create();
    textLabel->setString(label);
    textLabel->setFontSize(fontSize);
    textLabel->setColor(color);
    textLabel->setPosition(position);
    return textLabel;
}
