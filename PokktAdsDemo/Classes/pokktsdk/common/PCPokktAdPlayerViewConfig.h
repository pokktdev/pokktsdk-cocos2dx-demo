//
//  PCPokktAdPlayerViewConfig.h
//  Cocos2dxV3xPlugin
//
//  Created by Pokkt on 09/02/17.
//
//

#ifndef PCPokktAdPlayerViewConfig_h
#define PCPokktAdPlayerViewConfig_h


#include <string>


namespace pokkt
{
    class PCPokktAdPlayerViewConfig
    {
    public:
        
        // optional
        int defaultSkipTime;
        bool shouldAllowSkip;
        bool shouldAllowMute;
        bool shouldConfirmSkip;
        bool shouldCollectFeedback;
        
        std::string skipConfirmMessage;
        std::string skipConfirmYesLabel;
        std::string skipConfirmNoLabel;
        std::string skipTimerMessage;
        std::string incentiveMessage;
    };
}

#endif /* PCPokktAdPlayerViewConfig_h */



