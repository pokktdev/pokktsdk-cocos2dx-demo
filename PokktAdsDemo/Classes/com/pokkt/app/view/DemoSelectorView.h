#ifndef __CocosPokktApp__DemoSelectorView__
#define __CocosPokktApp__DemoSelectorView__

#include <stdio.h>
#include "BaseView.h"
#include "../../../../pokktsdk/pokkt.h"
#include "ui/UIEditBox/UIEditBox.h"

using namespace cocos2d;
using namespace ui;
using namespace pokkt;


class DemoSelectorView : public BaseView, public ui::EditBoxDelegate
{
public:
    
    CREATE_FUNC(DemoSelectorView);
    
    virtual void handleBackPress(cocos2d::Ref* pSender);
    
    static DemoSelectorView* getView();
    
    ~DemoSelectorView();
    
protected:
    
    virtual bool init();
    
private:
    
    Button* _videoAds;
    Button* _interstitialAds;
    Button* _bannerAds;
    Button* _btnExportLog;
    
    EditBox* _screenNameEditBox;
    //ui::EditBox* editBox;
    // listeners
    void handleVideoAdsPokkt(Ref* pSender);
    void handleInterstitialAdsPokkt(Ref* pSender);
    void handleBannerAdsPokkt(Ref* pSender);
    
    void handleExportLog(Ref* pSender);
    
    
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);

    
    
};

#endif /* defined(__CocosPokktApp__DemoSelectorView__) */
