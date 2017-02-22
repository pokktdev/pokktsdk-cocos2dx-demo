#ifndef __CocosPokktApp__VideoAdsView__
#define __CocosPokktApp__VideoAdsView__


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

class VideoAdsView : public BaseView, public ui::EditBoxDelegate
{
public:
    
    CREATE_FUNC(VideoAdsView);
    
    virtual ~VideoAdsView();
    
    virtual void handleBackPress(cocos2d::Ref* pSender);
    
    static VideoAdsView* getView(std::string screenName);
    
protected:
    
    virtual bool init();
    
private:
    
    Button* _btnCacheRewardedVideoAd;
    Button* _btnShowRewardedVideoAd;
    Button* _btnCacheNonRewardedVideoAd;
    Button* _btnShowNonRewardedVideoAd;

    Text* _txtPointsEarned;
    
    Text* _txtStatus;
    
    float _coinsEarned;
    
    EditBox* _screenNameEditBox;
    
    // handlers
    void handleCacheRewardedVideoAd(Ref* pSender);
    void handleShowRewardedVideoAd(Ref* pSender);
    void handleCacheNonRewardedVideoAd(Ref* pSender);
    void handleShowNonRewardedVideoAd(Ref* pSender);
    
    // pokkt handlers
    void handleAdAvailability(std::string, bool, std::string);
    void handleAdCachingCompleted(std::string, bool, std::string);
    void handleAdCachingFailed(std::string, bool, std::string);
    void handleAdDisplayed(std::string, bool, std::string);
    void handleAdSkipped(std::string, bool, std::string);
    void handleAdCompleted(std::string, bool, std::string);
    void handleAdClosed(std::string, bool, std::string);
    void handleAdGratified(std::string, bool, std::string);
    
    void editBoxEditingDidBegin(EditBox* editBox);
    void editBoxEditingDidEnd(EditBox* editBox);
    void editBoxTextChanged(EditBox* editBox, const std::string& text);
    void editBoxReturn(EditBox* editBox);
    

};


#endif /* VideoAdsView_h */
