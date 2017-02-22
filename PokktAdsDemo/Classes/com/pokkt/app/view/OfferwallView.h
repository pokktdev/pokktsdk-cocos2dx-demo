#ifndef __CocosPokktApp__OfferwallView__
#define __CocosPokktApp__OfferwallView__

#include <stdio.h>
#include "BaseView.h"
#include "cocos2d.h"
#include "../../../../../cocos2d/cocos/ui/UIButton.h"
#include "../../../../../cocos2d/cocos/ui/UIText.h"
#include "../../../../../cocos2d/cocos/ui/UITextField.h"
#include "../../../../../cocos2d/cocos/ui/UICheckBox.h"
#include "../../../../pokktsdk/pokkt.h"

using namespace cocos2d;
using namespace ui;
using namespace pokkt;


class OfferwallView : public BaseView
{
public:
    
    CREATE_FUNC(OfferwallView);
    
    virtual ~OfferwallView();
    
    static OfferwallView* getView();
    
    virtual void handleBackPress(Ref *pSender);
    virtual void handleEnterForeground();
    
protected:
    
    virtual bool init();
    
private:

    Button* _btnGetOfferwallAny;
    Button* _btnGetOfferwallFix;
    Button* _btnIncompleteCallback;
    Button* _btnExportLog;
    
    Text* _txtPointsEarned;
    TextField* _txiEnterMaxPoints;
    CheckBox* _chkCloseOnSuccess;
    
    int _coinsEarned;
    
    // handlers
    void handleGetOfferwallAny(Ref* pSender);
    void handleGetOfferwallFix(Ref* pSender);
    void handleIncompleteCallback(Ref* pSender);
    void handleExportLog(Ref* pSender);
    
    // pokkt handlers
    void handleCoinResponse(std::string coins);
    void handleCoinResponseWithTrId(std::string coinsWithTrId);
    void handleCoinResponseFailed(std::string message);
    void handleCampaignAvailibity(std::string message);
    void handleOfferwallclosed(std::string message);
};

#endif /* defined(__CocosPokktApp__OfferwallView__) */
