#ifndef __CocosPokktApp__AdDemoView__
#define __CocosPokktApp__AdDemoView__

#include <stdio.h>
#include "BaseView.h"
#include "cocos2d.h"
#include "../../../../../cocos2d/cocos/ui/UIButton.h"
#include "../../../../../cocos2d/cocos/ui/UIText.h"
#include "../../../../pokktsdk/pokkt.h"

using namespace cocos2d;
using namespace ui;
using namespace pokkt;


class AdDemoView : public BaseView
{
public:
    
    CREATE_FUNC(AdDemoView);
    
    virtual ~AdDemoView();
    
    virtual void handleBackPress(cocos2d::Ref* pSender);
    
    void setAdConfig(PCAdConfig* adConfig);
    
    static AdDemoView* getView(std::string screenName);
    
protected:
    
    virtual bool init();
    
private:
        
    Button* _btnCacheVideoAd;
    Button* _btnShowVideoAd;
    Button* _btnCacheInterstitialAd;
    Button* _btnShowInterstitialAd;
    
    Button* _btnExportLog;
    
    Text* _txtScreenName;
    Text* _txtPointsEarned;
    Text* _txtStatus;
    
    float _coinsEarned;
    PCAdConfig* _adConfig;
    
    // handlers
    void handleCacheVideoAd(Ref* pSender);
    void handleShowVideoAd(Ref* pSender);
    void handleCacheInterstitialAd(Ref* pSender);
    void handleShowInterstitialAd(Ref* pSender);
    void handleExportLog(Ref* pSender);
    
    // pokkt handlers
    void handleAdAvailability(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
    void handleAdCachingCompleted(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
    void handleAdCachingFailed(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
    void handleAdDisplayed(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
    void handleAdSkipped(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
    void handleAdCompleted(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
    void handleAdClosed(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
    void handleAdGratified(PCAdConfig* adConfig, std::map<std::string, std::string> extraValues);
};

#endif /* defined(__CocosPokktApp__AdDemoView__) */
