#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <PokktSDK/PokktSDK.h>
#import <PokktSDK/PokktAdConfig.h>
#import "IOSExtension.h"
#import "PCPokktAds.h"


/***
 *
 *  CONSTS
 *
 ***/

// operation names
#define     SET_POKKT_CONFIG                @"setPokktConfig"
#define     SET_THIRDPARTY_ID               @"setThirdPartyUserId"
#define     SET_PLAYER_VIEW_CONFIG          @"setAdPlayerViewConfig"
#define     SET_USER_DETAILS                @"setUserDetails"

#define     VIDEO_AD_CACHE_REWARDED                     @"VideoAd.cacheRewarded"
#define     VIDEO_AD_CACHE_NON_REWARDED                 @"VideoAd.cacheNonRewarded"
#define     VIDEO_AD_SHOW_REWARDED                      @"VideoAd.showRewarded"
#define     VIDEO_AD_SHOW_NON_REWARDED                  @"VideoAd.showNonRewarded"
#define     VIDEO_AD_CHECK_AVAILABILITY_REWARDED        @"VideoAd.checkAdAvailability.rewarded"
#define     VIDEO_AD_CHECK_AVAILABILITY_NON_REWARDED    @"VideoAd.checkAdAvailability.nonRewarded"

#define     INTERSTITIAL_AD_CACHE_REWARDED                      @"Interstitial.cacheRewarded"
#define     INTERSTITIAL_AD_CACHE_NON_REWARDED                  @"Interstitial.cacheNonRewarded"
#define     INTERSTITIAL_AD_SHOW_REWARDED                       @"Interstitial.showRewarded"
#define     INTERSTITIAL_AD_SHOW_NON_REWARDED                   @"Interstitial.showNonRewarded"
#define     INTERSTITIAL_AD_CHECK_AVAILABILITY_REWARDED         @"Interstitial.checkAdAvailability.rewarded"
#define     INTERSTITIAL_AD_CHECK_AVAILABILITY_NON_REWARDED     @"Interstitial.checkAdAvailability.nonRewarded"

#define     BANNER_LOAD                     @"Banner.loadBanner"
#define     BANNER_LOAD_WITH_RECT           @"Banner.loadBannerWithRect"
#define     BANNER_DESTROY                  @"Banner.destroyBanner"
#define     BANNER_SHOULD_AUTO_REFRESH      @"Banner.shouldAutoRefresh"

#define     IN_GAME_ADS_FETCH_ASSETS        @"InGameAd.fetchAssets"

#define     ANALYTICS_SET_DETAILS           @"Analytics.setAnalyticsDetails"
#define     ANALYTICS_TRACK_IAP             @"Analytics.trackIAP"
#define     ANALYTICS_NOTIFY_APP_INSTALL    @"Analytics.notifyAppInstall"
#define     ANALYTICS_UPDATE_IGA_DATA       @"Analytics.updateIGAData"

#define     DEBUGGING_SHOULD_DEBUG          @"Debugging.shouldDebug"
#define     DEBUGGING_EXPORT_LOG            @"Debugging.exportLog"
#define     DEBUGGING_EXPORT_LOG_TO_CLOUD   @"Debugging.exportLogToCloud"
#define     DEBUGGING_SHOW_TOAST            @"Debugging.showToast"
#define     DEBUGGING_SHOW_LOG              @"Debugging.showLog"


/***
 *  Pokkt-to-Framework Events
 ***/

// Video/Interstitial Ad Delegate
#define     AD_CACHING_COMPLETED_EVENT      @"AdCachingCompleted"
#define     AD_CACHING_FAILED_EVENT         @"AdCachingFailed"
#define     AD_CLOSED_EVENT                 @"AdClosed"
#define     AD_COMPLETED_EVENT              @"AdCompleted"
#define     AD_FAILED_TO_SHOW_EVENT         @"AdFailedToShow"
#define     AD_DISPLAYED_EVENT              @"AdDisplayed"
#define     AD_SKIPPED_EVENT                @"AdSkipped"
#define     AD_GRATIFIED_EVENT              @"AdGratified"
#define     AD_AVAILABILITY_EVENT           @"AdAvailability"

// Banner Ad Delegate
#define     BANNER_LOADED                   @"BannerLoaded"
#define     BANNER_LOAD_FAILED              @"BannerLoadFailed"

// IGA Delegate
#define     IGA_ASSETS_READY                @"IGAAssetsReady"
#define     IGA_ASSETS_FAILED               @"IGAAssetsFailed"


// banner related
#define     TOP_LEFT        1
#define     TOP_CENTER      2
#define     TOP_RIGHT       3
#define     MIDDLE_LEFT     4
#define 	MIDDLE_CENTER   5
#define 	MIDDLE_RIGHT    6
#define 	BOTTOM_LEFT     7
#define     BOTTOM_CENTER   8
#define     BOTTOM_RIGHT    9




/***
 *
 * DEFINITIONS
 *
 ***/

typedef void (^CaseBlock)(NSString* params);


// utils
UIViewController* getRootViewController();
NSDictionary* extractJSON(NSString* jsonString);
PokktIAPDetails* parseIAPDetails(NSString* detailsString);
PokktAdPlayerViewConfig* getAdPlayerViewConfigFromJSONString(NSString* configString);
PokktUserInfo* getUserDetailsFromJSONString(NSString* stringData);
PokktAnalyticsDetails* getAnalyticsDetailsFromJSONString(NSString* stringData);
NSString* stringifyJSONDictionary(NSDictionary *jsonObject);
NSString* getReturnParamsFromValues(NSString* _Nonnull screenName,
                                    bool isRewarded,
                                    AdFormatType adFormat,
                                    NSMutableDictionary<NSString *, id> *paramList);


// banner-util methods
void topLeft(UIView * view);
void topRight(UIView * view);
void topCenter(UIView * view);
void middleLeft(UIView* view);
void middleRight(UIView * view);
void middleCenter(UIView * view);
void bottomLeft(UIView * view);
void bottomRight(UIView * view);
void bottomCenter(UIView * view);




/***
 *
 * ADAPTER
 *
 ***/

static PokktBannerView* bannerContainer;
static NSDictionary *operations = nil;

static BOOL delegateAssigned = false;

@interface PokktAdsAdapter : NSObject<PokktVideoAdsDelegate, PokktInterstitialDelegate, PokktBannerDelegate, PokktIGADelegate>

+ (void) processForOperation:(NSString*)operation withParams:(NSString*)params;

@end




/***
 *
 *  NATIVE EXTENSION
 *  - these are exposed to the framework
 *  - frameworks will call these to communicate
 *
 ***/

void notifyNative(const char *operation, const char *args)
{
    NSString *op = [NSString stringWithUTF8String:(operation)];
    NSString *params = [NSString stringWithUTF8String:(args)];
    
    [PokktAdsAdapter processForOperation:op withParams:params];
    
    if (!delegateAssigned)
    {
        PokktAdsAdapter *adapter = [[PokktAdsAdapter alloc] init];
        [PokktVideoAds setPokktVideoAdsDelegate:adapter];
        [PokktInterstial setPokktInterstitialDelegate:adapter];
        [PokktBanner setPokktBannerDelegate:adapter];
        //[PokktInGameAd setIGADelegate:adapter];
        
        delegateAssigned = true;
    }
}

const char* getSDKVersionOnNative()
{
    const char* version = [[NSString stringWithFormat:@"%@", [PokktAds getSDKVersion]] UTF8String];
    return version;
}

// cocos2dx bridge
void notifyIOS(const char *operation, const char *args)
{
    notifyNative(operation, args);
}

const char* getSDKVersionOnIOS()
{
    return getSDKVersionOnNative();
}



/***
 *
 *  POKKT-TO-FRAMEWORK
 *
 ***/

void notifyFramework(NSString *operation, NSString *param)
{
    pokkt::PCPokktAds::handleNativeMessage([operation UTF8String], [param UTF8String]);
}



/***
 *
 *  ADATPTER: implementation
 *
 ***/

@implementation PokktAdsAdapter

+ (NSDictionary*) getOperationList
{
    if (operations == nil)
    {
        operations =
        @{
          // Common APIs
          SET_POKKT_CONFIG:
              ^(NSString *params) {
                  NSDictionary *jsonObject = extractJSON(params);
                  NSString *appId = jsonObject[@"appId"];
                  NSString *securityKey = jsonObject[@"securityKey"];
                  [PokktAds setPokktConfigWithAppId:appId securityKey:securityKey];
              },
          
          SET_THIRDPARTY_ID:
              ^(NSString *params) {
                  [PokktAds setThirdPartyUserId:params];
              },
          
          SET_PLAYER_VIEW_CONFIG:
              ^(NSString *params) {
                  [PokktAds setPokktAdPlayerViewConfig:getAdPlayerViewConfigFromJSONString(params)];
              },
          
          SET_USER_DETAILS:
              ^(NSString *params) {
                  [PokktAds setUserDetails:getUserDetailsFromJSONString(params)];
              },
          
          
          // Video Ads APIs
          VIDEO_AD_CACHE_REWARDED:
              ^(NSString *params) {
                  [PokktVideoAds cacheRewarded:params];
              },
          
          VIDEO_AD_CACHE_NON_REWARDED:
              ^(NSString *params) {
                  [PokktVideoAds cacheNonRewarded:params];
              },
          
          VIDEO_AD_SHOW_REWARDED:
              ^(NSString *params) {
                  [PokktVideoAds showRewarded:params withViewController:getRootViewController()];
              },
          
          VIDEO_AD_SHOW_NON_REWARDED:
              ^(NSString *params) {
                  [PokktVideoAds showNonRewarded:params withViewController:getRootViewController()];
              },
          
          VIDEO_AD_CHECK_AVAILABILITY_REWARDED:
              ^(NSString *params) {
                  [PokktVideoAds checkRewardedAdAvailability:params];
              },
          
          VIDEO_AD_CHECK_AVAILABILITY_NON_REWARDED:
              ^(NSString *params) {
                  [PokktVideoAds checkNonRewardedAdAvailability:params];
              },
          
          
          // Interstitial APIs
          INTERSTITIAL_AD_CACHE_REWARDED:
              ^(NSString *params) {
                  [PokktInterstial cacheRewarded:params];
              },
          
          INTERSTITIAL_AD_CACHE_NON_REWARDED:
              ^(NSString *params) {
                  [PokktInterstial cacheNonRewarded:params];
              },
          
          INTERSTITIAL_AD_SHOW_REWARDED:
              ^(NSString *params) {
                  [PokktInterstial showRewarded:params withViewController:getRootViewController()];
              },
          
          INTERSTITIAL_AD_SHOW_NON_REWARDED:
              ^(NSString *params) {
                  [PokktInterstial showNonRewarded:params withViewController:getRootViewController()];
              },
          
          INTERSTITIAL_AD_CHECK_AVAILABILITY_REWARDED:
              ^(NSString *params) {
                  [PokktInterstial checkRewardedAdAvailability:params];
              },
          
          INTERSTITIAL_AD_CHECK_AVAILABILITY_NON_REWARDED:
              ^(NSString *params) {
                  [PokktInterstial checkNonRewardedAdAvailability:params];
              },
          
          
          // Banner Ads APIs
          BANNER_LOAD:
              ^(NSString *params) {
                  NSDictionary* jsonObject = extractJSON(params);
                  NSString* screenName = jsonObject[@"screenName"];
                  int position = [jsonObject[@"bannerPosition"] intValue];
                  
                  if (bannerContainer != NULL)
                  {
                      [PokktBanner destroyBanner:bannerContainer];
                      bannerContainer = NULL;
                  }
                  
                  bannerContainer = [[PokktBannerView alloc] initWithFrame:CGRectMake(0, 0, 320, 50)];
                  bannerContainer.translatesAutoresizingMaskIntoConstraints = NO;
                  
                  [getRootViewController().view addSubview:bannerContainer];
                  
                  switch (position)
                  {
                      case 1: topLeft(bannerContainer);       break;
                      case 2: topCenter(bannerContainer);     break;
                      case 3: topRight(bannerContainer);      break;
                      case 4: middleLeft(bannerContainer);    break;
                      case 5: middleCenter(bannerContainer);  break;
                      case 6: middleRight(bannerContainer);   break;
                      case 7: bottomLeft(bannerContainer);    break;
                      case 8: bottomCenter(bannerContainer);  break;
                      case 9: bottomRight(bannerContainer);   break;
                      default: topCenter(bannerContainer);    break;
                  }
                  
                  [PokktBanner loadBanner:bannerContainer withScreenName:screenName rootViewContorller:getRootViewController()];
              },
          
          BANNER_LOAD_WITH_RECT:
              ^(NSString *params) {
                  NSDictionary *jsonObject = extractJSON(params);
                  
                  NSString *screenName = jsonObject[@"screenName"];
                  int width = [jsonObject[@"width"] intValue];
                  int height = [jsonObject[@"height"] intValue];
                  float x = [jsonObject[@"x"] floatValue];
                  float y = [jsonObject[@"y"]floatValue];
                  
                  if (bannerContainer != NULL)
                  {
                      [PokktBanner destroyBanner:bannerContainer];
                      bannerContainer = NULL;
                  }
                  
                  bannerContainer = [[PokktBannerView alloc] initWithFrame:CGRectMake(x, y, width, height)];
                  [getRootViewController().view addSubview:bannerContainer];
                  
                  [PokktBanner loadBanner:bannerContainer withScreenName:screenName rootViewContorller:getRootViewController()];
              },
          
          BANNER_DESTROY:
              ^(NSString *params) {
                  [PokktBanner destroyBanner:bannerContainer];
              },
          
          BANNER_SHOULD_AUTO_REFRESH:
              ^(NSString *params) {
                  [PokktBanner setBannerAutoRefresh:[params boolValue]];
              },
          
          
          // IGA APIs
          IN_GAME_ADS_FETCH_ASSETS:
              ^(NSString *params) {
                  [PokktInGameAd fetchIGAAssets:params];
              },
          
          
          // Analytics APIs
          ANALYTICS_SET_DETAILS:
              ^(NSString *params) {
                  [PokktAds setPokktAnalyticsDetail:getAnalyticsDetailsFromJSONString(params)];
              },
          
          ANALYTICS_NOTIFY_APP_INSTALL:
              ^(NSString *params) {
                  [PokktAds notifyAppInstall];
              },
          
          ANALYTICS_TRACK_IAP:
              ^(NSString *params) {
                  [PokktAds trackIAP:parseIAPDetails(params)];
              },
          
          ANALYTICS_UPDATE_IGA_DATA:
              ^(NSString *params) {
                  //[PokktAds updateIGAData:params];
              },
          
          
          // Debugging APIs
          DEBUGGING_SHOULD_DEBUG:
              ^(NSString *params) {
                  [PokktDebugger setDebug:[params boolValue]];
              },
          
          DEBUGGING_SHOW_LOG:
              ^(NSString *params) {
                  [PokktDebugger printLog:params];
              },
          
          DEBUGGING_SHOW_TOAST:
              ^(NSString *params) {
                  [PokktDebugger showToast:params viewController:getRootViewController()];
              },
          
          DEBUGGING_EXPORT_LOG:
              ^(NSString *params) {
                  [PokktDebugger exportLog:getRootViewController()];
              }
          };
    }
    
    return operations;
}

+ (void) processForOperation:(NSString*)operation withParams:(NSString*)params
{
    operations = nil;
    NSDictionary *opsList = [self getOperationList];
    CaseBlock block = (CaseBlock)opsList[operation];
    if (block)
    {
        block(params);
    }
    else
    {
        NSLog(@"[POKKT-NATIVE] Unknown operation requested: %@", operation);
    }
}




/***
 * Video Ad Delegate
 ***/

- (void) videoAdCachingCompleted:(NSString *) screenName isRewarded: (BOOL)isRewarded reward: (float)reward
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = [[NSNumber numberWithFloat:reward] stringValue];
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, additionalParams);
    
    notifyFramework(AD_CACHING_COMPLETED_EVENT, params);
}

- (void) videoAdCachingFailed: (NSString *)screenName isRewarded: (BOOL)isRewarded errorMessage: (NSString *)errorMessage
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = errorMessage;
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, additionalParams);
    
    notifyFramework(AD_CACHING_FAILED_EVENT, params);
}

- (void) videoAdCompleted: (NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, nil);
    
    notifyFramework(AD_COMPLETED_EVENT, params);
}

- (void) videoAdDisplayed: (NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, nil);
    
    notifyFramework(AD_DISPLAYED_EVENT, params);
}

- (void) videoAdGratified: (NSString *)screenName reward:(float)reward
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = [[NSNumber numberWithFloat:reward] stringValue];
    NSString *params = getReturnParamsFromValues(screenName, true, VIDEO, additionalParams);
    
    notifyFramework(AD_GRATIFIED_EVENT, params);
}

- (void) videoAdSkipped: (NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, nil);
    
    notifyFramework(AD_SKIPPED_EVENT, params);
}

- (void) videoAdClosed:(NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, nil);
    
    notifyFramework(AD_CLOSED_EVENT, params);
}

- (void) videoAdAvailabilityStatus: (NSString *)screenName isRewarded: (BOOL)isRewarded isAdAvailable: (BOOL)isAdAvailable
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = isAdAvailable ? @"true" : @"false";
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, additionalParams);
    
    notifyFramework(AD_AVAILABILITY_EVENT, params);
}

- (void) videoAdFailedToShow: (NSString *)screenName isRewarded: (BOOL)isRewarded errorMessage: (NSString *)errorMessage
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = errorMessage;
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, VIDEO, additionalParams);
    
    notifyFramework(AD_FAILED_TO_SHOW_EVENT, params);
}


/***
 * Interstitial Delegate
 ***/

- (void) interstitialCachingCompleted:(NSString *) screenName isRewarded: (BOOL)isRewarded reward: (float)reward
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = [[NSNumber numberWithFloat:reward] stringValue];
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, additionalParams);
    
    notifyFramework(AD_CACHING_COMPLETED_EVENT, params);
}

- (void) interstitialCachingFailed: (NSString *)screenName isRewarded: (BOOL)isRewarded errorMessage: (NSString *)errorMessage
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = errorMessage;
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, additionalParams);
    
    notifyFramework(AD_CACHING_FAILED_EVENT, params);
}

- (void) interstitialCompleted: (NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, nil);
    
    notifyFramework(AD_COMPLETED_EVENT, params);
}

- (void) interstitialDisplayed: (NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, nil);
    
    notifyFramework(AD_DISPLAYED_EVENT, params);
}

- (void) interstitialGratified: (NSString *)screenName reward:(float)reward
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = [[NSNumber numberWithFloat:reward] stringValue];
    NSString *params = getReturnParamsFromValues(screenName, true, INTERSTITIAL, additionalParams);
    
    notifyFramework(AD_GRATIFIED_EVENT, params);
}

- (void) interstitialSkipped: (NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, nil);
    
    notifyFramework(AD_SKIPPED_EVENT, params);
}

- (void) interstitialClosed:(NSString *)screenName isRewarded: (BOOL)isRewarded
{
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, nil);
    
    notifyFramework(AD_CLOSED_EVENT, params);
}

- (void) interstitialAvailabilityStatus: (NSString *)screenName isRewarded: (BOOL)isRewarded isAdAvailable: (BOOL)isAdAvailable
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = isAdAvailable ? @"true" : @"false";
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, additionalParams);
    
    notifyFramework(AD_AVAILABILITY_EVENT, params);
}

- (void) interstitialFailedToShow: (NSString *)screenName isRewarded: (BOOL)isRewarded errorMessage: (NSString *)errorMessage
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"ARGS"] = errorMessage;
    NSString *params = getReturnParamsFromValues(screenName, isRewarded, INTERSTITIAL, additionalParams);
    
    notifyFramework(AD_FAILED_TO_SHOW_EVENT, params);
}


/***
 * Banner Ads Delegate
 ***/

- (void)bannerLoaded:(NSString *)screenName
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"SCREEN_NAME"] = screenName;
    NSString *params = stringifyJSONDictionary(additionalParams);
    notifyFramework(BANNER_LOADED, params);
}

- (void)bannerLoadFailed:(NSString *)screenName errorMessage:(NSString *)errorMessage
{
    NSMutableDictionary *additionalParams = [[NSMutableDictionary alloc] init];
    additionalParams[@"SCREEN_NAME"] = screenName;
    additionalParams[@"ARGS"] = errorMessage;
    NSString *params = stringifyJSONDictionary(additionalParams);
    
    notifyFramework(BANNER_LOAD_FAILED, params);
}


/***
 * IGA Delegate
 ***/

- (void)onIGAAssetsReady:(NSString *)screenName assetList:(NSString *)igaAssets
{
    notifyFramework(IGA_ASSETS_READY, igaAssets);
}

- (void)onIGAAssetsFailed: (NSString *)errorMessage
{
    notifyFramework(IGA_ASSETS_FAILED, errorMessage);
}

@end




/***
 *
 * UTILITIES
 *
 ***/

UIViewController* getRootViewController()
{
    UIViewController *viewController = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    return viewController;
}

NSDictionary* extractJSON(NSString* jsonString)
{
    NSError* jsonError;
    NSData* jsonData = [jsonString dataUsingEncoding:NSUTF8StringEncoding];
    NSDictionary* jsonObject = [NSJSONSerialization JSONObjectWithData:jsonData
                                                               options:NSJSONReadingMutableContainers
                                                                 error:&jsonError];
    return jsonObject;
}

PokktIAPDetails* parseIAPDetails(NSString* detailsString)
{
    NSDictionary* jsonObject = extractJSON(detailsString);
    
    PokktIAPDetails* details = [[PokktIAPDetails alloc] init];
    
    details.productIdentifier = jsonObject[@"productId"];
    details.productPrice = [NSString stringWithFormat:@"%d", [jsonObject[@"price"] intValue]];
    details.productCurrency = jsonObject[@"currencyCode"];
    details.productTitle = jsonObject[@"title"];
    details.productDescription = jsonObject[@"description"];
    
    // TODO
    //detail.setPurchaseData(jsonObject.optString("purchaseData"));
    //detail.setPurchaseSignature(jsonObject.optString("purchaseSignature"));
    //detail.setPurchaseStore(IAPStoreType.valueOf(jsonObject.optString("purchaseStore")));
    
    return details;
}

PokktAdPlayerViewConfig* getAdPlayerViewConfigFromJSONString(NSString* configString)
{
    NSDictionary* jsonObject = extractJSON(configString);
    
    PokktAdPlayerViewConfig* config = [[PokktAdPlayerViewConfig alloc] init];
    
    config.shouldAllowSkip = [jsonObject[@"shouldAllowSkip"] boolValue];
    config.defaultSkipTime = [jsonObject[@"defaultSkipTime"] floatValue];
    config.skipConfirmMessage = jsonObject[@"skipConfirmMessage"];
    config.shouldAllowMute = [jsonObject[@"shouldAllowMute"] boolValue];
    config.shouldConfirmSkip = [jsonObject[@"shouldSkipConfirm"] boolValue];
    config.skipConfirmYesLabel = jsonObject[@"skipConfirmYesLabel"];
    config.skipConfirmNoLabel = jsonObject[@"skipConfirmNoLabel"];
    config.skipTimerMessage = jsonObject[@"skipTimerMessage"];
    config.incentiveMessage = jsonObject[@"incentiveMessage"];
    
    return config;
}

PokktUserInfo* getUserDetailsFromJSONString(NSString* stringData)
{
    NSDictionary *jsonObject = extractJSON(stringData);
    
    PokktUserInfo *info = [[PokktUserInfo alloc] init];
    
    info.name = jsonObject[@"name"];
    info.age = jsonObject[@"age"];
    info.sex = jsonObject[@"sex"];
    info.mobileNumber = jsonObject[@"mobileNo"];
    info.emailAddress = jsonObject[@"emailAddress"];
    info.location = jsonObject[@"location"];
    info.birthday = jsonObject[@"birthday"];
    info.maritalStatus = jsonObject[@"maritalStatus"];
    info.facebookId = jsonObject[@"facebookId"];
    info.twitterHandle = jsonObject[@"twitterHandle"];
    info.educationInformation = jsonObject[@"education"];
    info.nationality = jsonObject[@"nationality"];
    info.employmentStatus = jsonObject[@"employment"];
    info.maturityRating = jsonObject[@"maturityRating"];
    
    return info;
}

PokktAnalyticsDetails* getAnalyticsDetailsFromJSONString(NSString* stringData)
{
    NSDictionary *jsonObject = extractJSON(stringData);
    
    PokktAnalyticsDetails *details = [[PokktAnalyticsDetails alloc] init];
    
    // analytics
    details.googleTrackerID = jsonObject[@"googleAnalyticsID"];
    details.mixPanelTrackerID = jsonObject[@"mixPanelProjectToken"];
    details.flurryTrackerID = jsonObject[@"flurryApplicationKey"];
    
    if(jsonObject[@"selectedAnalyticsType"] != nil && ![jsonObject[@"selectedAnalyticsType"] isEqual:@""])
    {
        if ([jsonObject[@"selectedAnalyticsType"] isEqual:@"FLURRY"])
            details.eventType = FLURRY_ANALYTICS;
        
        else if ([jsonObject[@"selectedAnalyticsType"] isEqual:@"GOOGLE_ANALYTICS"])
            details.eventType = GOOGLE_ANALYTICS;
        
        else if ([jsonObject[@"selectedAnalyticsType"] isEqual:@"MIXPANNEL"])
            details.eventType = MIXPANNEL_ANALYTICS;
    }
    
    return details;
}

NSString* getReturnParamsFromValues(NSString* _Nonnull screenName,
                                    bool isRewarded,
                                    AdFormatType adFormat,
                                    NSMutableDictionary<NSString *, id> *paramList)
{
    if (!paramList)
    {
        paramList = [[NSMutableDictionary alloc] init];
    }
    
    paramList[@"SCREEN_NAME"] = screenName;
    paramList[@"IS_REWARDED"] = isRewarded ? @"true" : @"false";;
    paramList[@"AD_FORMAT"] = [@(adFormat) stringValue];
    
    NSString *params = stringifyJSONDictionary(paramList);
    return params;
}


NSString* stringifyJSONDictionary(NSDictionary *jsonObject)
{
    NSError *jsonError;
    NSData *jsonData = [NSJSONSerialization dataWithJSONObject:jsonObject options:0 error:&jsonError];
    NSString *jsonString = [[NSString alloc] initWithData:jsonData encoding:NSUTF8StringEncoding];
    return jsonString;
}

NSLayoutConstraint* getLayoutConstraint(UIView* view, NSLayoutAttribute layoutAttribute1, NSLayoutRelation layoutRelation, UIView* toItem, NSLayoutAttribute layoutAttribute2, CGFloat multiplier, CGFloat constant)
{
    return [NSLayoutConstraint constraintWithItem:view
                                        attribute:layoutAttribute1
                                        relatedBy:layoutRelation
                                           toItem:toItem
                                        attribute:layoutAttribute2
                                       multiplier:multiplier
                                         constant:constant];
}

void updateBannerLocation(UIView* view, NSLayoutConstraint* leading, NSLayoutConstraint* bottom, NSLayoutConstraint* trailing, NSLayoutConstraint* height)
{
    [view addConstraint:trailing];
    [view.superview addConstraint:bottom];
    [view.superview addConstraint:leading];
    [view addConstraint:height];
}

//Top
void topLeft(UIView* view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeLeft, NSLayoutRelationEqual, view.superview, NSLayoutAttributeLeft, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeTop, NSLayoutRelationEqual, view.superview, NSLayoutAttributeTop, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

void topRight(UIView * view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeRight, NSLayoutRelationEqual, view.superview, NSLayoutAttributeRight, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeTop, NSLayoutRelationEqual, view.superview, NSLayoutAttributeTop, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

void topCenter(UIView * view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeCenterX, NSLayoutRelationEqual, view.superview, NSLayoutAttributeCenterX, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeTop, NSLayoutRelationEqual, view.superview, NSLayoutAttributeTop, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

// Middle
void middleLeft(UIView* view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeLeft, NSLayoutRelationEqual, view.superview, NSLayoutAttributeLeft, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeCenterY, NSLayoutRelationEqual, view.superview, NSLayoutAttributeCenterY, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

void middleRight(UIView * view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeRight, NSLayoutRelationEqual, view.superview, NSLayoutAttributeRight, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeCenterY, NSLayoutRelationEqual, view.superview, NSLayoutAttributeCenterY, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

void middleCenter(UIView * view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeCenterX, NSLayoutRelationEqual, view.superview, NSLayoutAttributeCenterX, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeCenterY, NSLayoutRelationEqual, view.superview, NSLayoutAttributeCenterY, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

//Bottom
void bottomLeft(UIView * view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeLeading, NSLayoutRelationEqual, view.superview, NSLayoutAttributeLeading, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeBottom, NSLayoutRelationEqual, view.superview, NSLayoutAttributeBottom, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

void bottomRight(UIView * view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeRight, NSLayoutRelationEqual, view.superview, NSLayoutAttributeRight, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeBottom, NSLayoutRelationEqual, view.superview, NSLayoutAttributeBottom, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}

void bottomCenter(UIView * view)
{
    NSLayoutConstraint* leading = getLayoutConstraint(view, NSLayoutAttributeCenterX, NSLayoutRelationEqual, view.superview, NSLayoutAttributeCenterX, 1.0f, 0.f);
    NSLayoutConstraint* bottom = getLayoutConstraint(view, NSLayoutAttributeBottom, NSLayoutRelationEqual, view.superview, NSLayoutAttributeBottom, 1.0f, 0.f);
    NSLayoutConstraint* trailing = getLayoutConstraint(view, NSLayoutAttributeWidth, NSLayoutRelationEqual, nil, NSLayoutAttributeWidth, 1.0f, 320);
    NSLayoutConstraint* height = getLayoutConstraint(view, NSLayoutAttributeHeight, NSLayoutRelationEqual, nil, NSLayoutAttributeNotAnAttribute, 0, 50);
    
    updateBannerLocation(view, leading, bottom, trailing, height);
}
