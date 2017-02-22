#ifndef PCEnums_h
#define PCEnums_h


namespace pokkt
{
    
    /**
     * pokkt-to-framework events
     **/
    //Video Ad Related Events
#define EVENT_VIDEO_AD_CACHING_COMPLETED                      "VideoAdCachingCompleted"
#define EVENT_VIDEO_AD_CACHING_FAILED                         "VideoAdCachingFailed"
#define EVENT_VIDEO_AD_CLOSED                                 "VideoAdClosed"
#define EVENT_VIDEO_AD_COMPLETED                              "VideoAdCompleted"
#define EVENT_VIDEO_AD_FAILED_TO_SHOW                         "VideoAdFailedToShow"
#define EVENT_VIDEO_AD_DISPLAYED                              "VideoAdDisplayed"
#define EVENT_VIDEO_AD_SKIPPED                                "VideoAdSkipped"
#define EVENT_VIDEO_AD_GRATIFIED                              "VideoAdGratified"
#define EVENT_VIDEO_AD_AVAILABILITY                           "VideoAdAvailability"
    
    //Interstitial Related Events
#define EVENT_INTERSTITIAL_CACHING_COMPLETED                      "InterstitialCachingCompleted"
#define EVENT_INTERSTITIAL_CACHING_FAILED                         "InterstitialCachingFailed"
#define EVENT_INTERSTITIAL_CLOSED                                 "InterstitialClosed"
#define EVENT_INTERSTITIAL_COMPLETED                              "InterstitialCompleted"
#define EVENT_INTERSTITIAL_FAILED_TO_SHOW                         "InterstitialFailedToShow"
#define EVENT_INTERSTITIAL_DISPLAYED                              "InterstitialDisplayed"
#define EVENT_INTERSTITIAL_SKIPPED                                "InterstitialSkipped"
#define EVENT_INTERSTITIAL_GRATIFIED                              "InterstitialGratified"
#define EVENT_INTERSTITIAL_AVAILABILITY                           "InterstitialAvailability"
    
    //Banner Related Events
#define EVENT_BANNER_LOADED_OP                   "BannerLoaded"
#define EVENT_BANNER_LOAD_FAILED_OP              "BannerLoadFailed"
    
    
    /**
     * implemented analytics types
     **/
#define POKKT_ANALYTICS_TYPE_NONE               "NONE"
#define POKKT_ANALYTICS_TYPE_GOOGLE_ANALYTICS   "GOOGLE_ANALYTICS"
#define POKKT_ANALYTICS_TYPE_MIXPANEL           "MIXPANEL"
#define POKKT_ANALYTICS_TYPE_FLURRY             "FLURRY"
#define POKKT_ANALYTICS_TYPE_FABRIC             "FABRIC"
    
    
    /**
     * in-app purchase store types
     **/
#define POKKT_IAP_STORE_TYPE_NONE       "NONE"
#define POKKT_IAP_STORE_TYPE_GOOGLE     "GOOGLE"
#define POKKT_IAP_STORE_TYPE_IOS        "IOS"
#define POKKT_IAP_STORE_TYPE_AMAZON     "AMAZON"
    

    /**
     * parameters name
     **/
#define REWARD              "REWARD"
#define BACK_PRESSED        "BACK_BUTTON"
#define FAIL_MESSAGE        "MESSAGE"
#define AD_VC               "AD_VC"
#define IS_AVAILABLE        "IS_AVAILABLE"
#define IS_READY            "IS_READY"
    
#define TOP_LEFT       1
#define TOP_CENTER     2
#define TOP_RIGHT      3
#define MIDDLE_LEFT    4
#define MIDDLE_CENTER  5
#define MIDDLE_RIGHT   6
#define BOTTOM_LEFT    7
#define BOTTOM_CENTER  8
#define BOTTOM_RIGHT   9

}

#endif /* PCEnums_h */
