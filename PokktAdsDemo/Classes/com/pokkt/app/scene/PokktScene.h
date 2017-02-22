#ifndef __POKKTAPP_SCENE_H__
#define __POKKTAPP_SCENE_H__

#include "cocos2d.h"
#include "../view/BaseView.h"
#include "../../../../pokktsdk/pokkt.h"

using namespace cocos2d;
using namespace ui;
using namespace pokkt;


class PokktScene : public LayerColor
{
public:
    
    static Scene* createScene();
    
    void handleEnterForeground();
    
    CREATE_FUNC(PokktScene);
    
protected:
    
    virtual bool init();
    virtual void onKeyRelease(EventKeyboard::KeyCode keyCode, Event* event);
    void initVersion(const std::string &version);
    
private:
    
    void handleChangeScene(Ref* pSender);
    void handleCloseCallback(Ref* pSender);
    
    // view
    BaseView* _currentView;
};

#endif // __POKKTAPP_SCENE_H__
