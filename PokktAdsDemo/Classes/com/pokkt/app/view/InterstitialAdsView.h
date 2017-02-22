#ifndef __CocosPokktApp__InterstitialAdsView__
#define __CocosPokktApp__InterstitialAdsView__


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

class InterstitialAdsView : public BaseView, public ui::EditBoxDelegate
{
public:
    
    CREATE_FUNC(InterstitialAdsView);
    
    virtual ~InterstitialAdsView();
    
    virtual void handleBackPress(cocos2d::Ref* pSender);
    
    static InterstitialAdsView* getView(std::string screenName);
    
protected:
    
    virtual bool init();
    
private:
    
    Button* _btnCacheRewardedInterstitialAd;
    Button* _btnShowRewardedInterstitialAd;
    Button* _btnCacheNonRewardedInterstitialAd;
    Button* _btnShowNonRewardedInterstitialAd;
    
    Text* _txtPointsEarned;
    Text* _txtStatus;
    
    float _coinsEarned;
    
    EditBox* _screenNameEditBox;
    
    // handlers
    void handleCacheRewardedInterstitialAd(Ref* pSender);
    void handleShowRewardedInterstitialAd(Ref* pSender);
    void handleCacheNonRewardedInterstitialAd(Ref* pSender);
    void handleShowNonRewardedInterstitialAd(Ref* pSender);
    
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

#endif /* InterstitialAdsView_h */
