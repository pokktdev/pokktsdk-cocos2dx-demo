#ifndef __CocosPokktApp__BannerAdsView__
#define __CocosPokktApp__BannerAdsView__


#include <stdio.h>
#include "BaseView.h"
#include "cocos2d.h"
#include "../../../../../cocos2d/cocos/ui/UIButton.h"
#include "../../../../../cocos2d/cocos/ui/UIText.h"
#include "../../../../pokktsdk/pokkt.h"
#include "ui/UIEditBox/UIEditBox.h"

using namespace cocos2d;
using namespace ui;
using namespace pokkt;

class BannerAdsView : public BaseView, public ui::EditBoxDelegate
{
public:
    
    CREATE_FUNC(BannerAdsView);
    
    virtual ~BannerAdsView();
    
    virtual void handleBackPress(cocos2d::Ref* pSender);
    
    static BannerAdsView* getView(std::string screenName);
    
protected:
    
    virtual bool init();
    
private:
    
    Button* _btnLoadTopBannerAd;
    Button* _btnDestroyTopBannerAd;
    
    float _coinsEarned;
    Text* _txtStatus;    
    EditBox* _screenNameEditBox;
    
    // handlers
    void handleLoadTopBannerAd(Ref* pSender);
    void handleDestroyTopBannerAd(Ref* pSender);
    void handleLoadBottomBannerAd(Ref* pSender);
    void handleDestroyBottomBannerAd(Ref* pSender);
    
    void handleBannerLoadSuccessfuly(std::string, bool, std::string);
    void handleBannerLoadFailed(std::string, bool, std::string);
    
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
    
    
};

#endif /* BannerAdsView_h */
