#POKKT SDK Cocos2d-x Integration Guide (v6.0)

##Overview
Thank you for choosing Pokkt SDK for Cocos2dx . This document contains all the information required to set up the SDK with your project. 

We also support mediation for various third party networks. To know the supported third party networks and their integration process go to plugins section . 

Before implementing plugins it is mandatory to go through configuration setup and implementation steps , as these sections contain mandatory steps to be followed by every
plugin integration.

There is a “Sample app” provided . We will be referencing this app during the course of explanation in this document. We suggest you go through the sample app for better understanding.


##Project Configuration (Android)###Dependencies● Extract the PokktSDK_Native_Extension.zip file and put the content inside your C++ project, preferably directly inside the C lasses folder.<br>● Add moat.jar, comscore.jar, PokktSDK_v6.0.jar, android-support-v4.jar and PAPCocos2dx.jar to your project.<br>
● We expect Google play services integrated in project, although it;s optional but we recommend you to integrate it, as it’s required to fetch AdvertisingID for device,which is usefulto deliver targeted advertising to Android users.
##Manifest###Permissions DeclarationsWe have added the following permissions to the manifest
####1. Mandatory permissions.

~~~<uses-permission android:name=“android.permission.INTERNET” /><uses-permission android:name=“android.permission.READ_PHONE_STATE” />
~~~● **android.permission.INTERNET** = Required for SDK communication with server.<br>● **android.permission.READ_PHONE_STATE** = Required for creating unique identifier for you application based on the unique id of the device like IMEI.<br>

####2. Optional permissions.
	
~~~<uses-permission android:name=“android.permission.ACCESS_NETWORK_STATE” /><uses-permission android:name=“android.permission.ACCESS_WIFI_STATE” /><uses-permission android:name=“android.permission.CHANGE_WIFI_STATE” /><uses-permission android:name=“android.permission.WAKE_LOCK” /><uses-permission android:name=“android.permission.WRITE_EXTERNAL_STORAGE” /><uses-permission android:name=“android.permission.WRITE_CALENDAR” /><uses-permission android:name=“android.permission.ACCESS_COARSE_LOCATION” /><uses-permission android:name=“android.permission.ACCESS_FINE_LOCATION” /><uses-permission android:name=“android.permission.CALL_PHONE” /><uses-permission android:name=“android.permission.SEND_SMS” />
~~~
● **android.permission.ACCESS_NETWORK_STATE** = Required to detect changes in network, like if WIFI is available or not.<br>
	● **android.permission.ACCESS_WIFI_STATE** = Required to detect changes in network, like if WIFI is available or not.<br>● **android.permission.CHANGE_WIFI_STATE** = Required to detect changes in network, like if WIFI is available or not.<br>● a**ndroid.permission.WAKE_LOCK** = Required to prevent device from going into the sleep mode during video play.<br>● **android.permission.WRITE_EXTERNAL_STORAGE** = Required to store media files related to ads in external SD card, if not provided we will use app cache folder to store media files, which will result in unnecessary increase in application’s size. It isrecommended to ask for this permission as low end devices generally have less internally memory available.<br>● **android.permission.WRITE_CALENDAR** = Some Ads create events in calendar.<br>● **android.permission.ACCESS_COARSE_LOCATION** = Some Ads show content based on user’s location.<br>● **android.permission.ACCESS_FINE_LOCATION** = Some Ads show content based on user’s location<br>● **android.permission.CALL_PHONE** = Some Ads are interactive and they provide you a way to call directly from the content.<br>● **android.permission.SEND_SMS** = Some Ads are interactive and they provide you a way to send message.
###Activity DeclarationAdd the following activity in your AndroidManifest for Pokkt SDK integration.

~~~<activityandroid:name="com.pokkt.sdk.userinterface.presenter.activity.PokktAdActivity"android:configChanges="keyboard|keyboardHidden|navigation|orientation|screenLayout|uiMode|screenSize|smallestScreenSize"android:hardwareAccelerated="true"android:label=”Pokkt”android:screenOrientation="landscape"android:windowSoftInputMode="stateAlwaysHidden|adjustUnspecified" />

~~~You can change the android:screenOrientation="landscape" to of your choice, the way you want to display the ads.###Service DeclarationWe have added the following service in your AndroidManifest for receiving InApp notifications.

~~~<serviceandroid:name="com.pokkt.sdk.notification.NotificationService"android:exported="false"android:label="PokktNotificationService" />
~~~



##Project Configuration (iOS)
###Dependencies
The Pokkt SDK v6.0 for Cocos2dx comes in two zip files:<br>
a. pokktsdk.zip<br>
b. libpokkt.zip

**Step 1**. Extract the pokktsdk.zip file and put the content inside your C++ project, preferably
directly inside the ‘Classes’ folder.

**Step 2**. Extract and libpokkt.zip and add its content to your project. It should automatically add
the PokktSDK.framework and ComScore.framework . Just to make sure, go to your project’s settings’s “ Build Phases -> Link Binary with Libraries ”. If PokktSDK.framework and ComScore.framework is not present then make an entry there and you are good to go.

**Step 3**. Make sure to add the above “ PokktSDK.bundle ” to the your project.

**Step 4**. Ensure the followings frameworks are present(linked) inside project setting’s **“ Build-Phases -> Link Binaries With Libraries ”**, if not than add them manually:

~~~
● CoreData .framework
● Foundation .framework
● MediaPlayer .framework
● SystemConfiguration .framework
● UIKit .framework
● CoreTelephony .framework
● EventKit .framework
● AdSupport .framework
● CoreGraphics .framework
~~~

**Step 5**. Ensure that “ -ObjC ” flag is set inside project setting’s **“ Build Settings -> Other Linker
Flags ”**.

**Step 6**. In order to use PokktSDK’s background fetch functionality, enable **” Capabilities ->
Background Modes -> Background Fetch “** inside project settings. Then write the following code-snippet inside **“ didFinishLaunchingWithOptions ”** method of app-delegate class:

~~~
[application setMinimumBackgroundFetchInterval:
UIApplicationBackgroundFetchIntervalMinimum];
~~~

**Step 7**. Further, implement/update the background-fetch delegate methods in app-delegate class. Invoke **“ callBackgroundTaskCompletionHandler ”** method from
**“ performFetchWithCompletionHandler ”**. Observe the following code-snippet for reference:

~~~
-(void)application:(UIApplication *) application performFetchWithCompletionHandler:
(void(^)(UIBackgroundFetchResult))completionHandler
{
[PokktAds callBackgroundTaskCompletedHandler:
						^(UIBackgroundFetchResult result)
{
	completionHandler(result);
}];
}
~~~

**Step 8**. In order to enable local notifications for InApp Notifications , mention the following
inside **“didFinishLaunchingWithOptions”** method of the app-delegate class:

~~~
[application setMinimumBackgroundFetchInterval: UIApplicationBackgroundFetchIntervalMinimum];
UIUserNotificationSettings *settings = [UIUserNotificationSettings settingsForTypes:
(UIRemoteNotificationTypeBadge | UIRemoteNotificationTypeSound |
UIRemoteNotificationTypeAlert)
categories:nil];
[application registerUserNotificationSettings:settings];
~~~

**Step 9**. Invoke **“ inAppNotificationEvent ”** if the user taps on local notification, do this in the
**“ didReceiveLocalNotification ”** inside app-delegate class. Check the following reference:

~~~
-(void)application:(UIApplication*) application
		didReceiveLocalNotification:(UILocalNotification*) notification
{
	[PokktAds inAppNotificationEvent:notification];
}
~~~

**Step 10**. Open project’s Info.plist as Source Code. Make an entry of the following:

~~~
<key>NSAppTransportSecurity</key>
<dict>
<key>NSExceptionDomains</key>
<dict>
<key> pokkt.com </key>
<dict>
<key>NSIncludesSubdomains</key>
<true/>
<key>NSExceptionAllowsInsecureHTTPLoads</key>
<true/>
<key>NSExceptionRequiresForwardSecrecy</key>
<false/>
<key>NSExceptionMinimumTLSVersion</key>
<string>TLSv1.2</string>
<key>NSThirdPartyExceptionAllowsInsecureHTTPLoads</key>
<false/>
<key>NSThirdPartyExceptionRequiresForwardSecrecy</key>
<true/>
<key>NSThirdPartyExceptionMinimumTLSVersion</key>
<string>TLSv1.2</string>
<key>NSRequiresCertificateTransparency</key>
<false/>
</dict>
<key> cloudfront.net </key>
<dict>
<key>NSIncludesSubdomains</key>
<true/>
<key>NSExceptionAllowsInsecureHTTPLoads</key>
<true/>
<key>NSExceptionRequiresForwardSecrecy</key>
<false/>
<key>NSExceptionMinimumTLSVersion</key>
<string>TLSv1.2</string>
<key>NSThirdPartyExceptionAllowsInsecureHTTPLoads</key>
<false/>
<key>NSThirdPartyExceptionRequiresForwardSecrecy</key>
<true/>
<key>NSThirdPartyExceptionMinimumTLSVersion</key>
<string>TLSv1.2</string>
<key>NSRequiresCertificateTransparency</key>
<false/>
</dict>
</dict>
</dict>
~~~
This should be inside the main “dict” node.

**Step 11**. Ensure that Enable Bitcode is set to false in the generated project’s Build Settings .

##Implementation Steps
###Ad Types
####Video
Video ad can be rewarded or non-rewarded. You can either cache the ad in advance or directly call show for it.

We suggest you to cache the ad in advance so as to give seamless play behaviour, In other case it will stream the video which may lead to unnecessary buffering delays depending on the network connection.

#####Rewarded
1. Cache Rewarded Ad:<br>
`PCPokktAds::cacheRewardedVideoAd(screenName)`

2. Show Rewarded Ad:<br>
`PCPokktAds::showRewardedVideoAd(screenName)`

3. Check Ad Availability Status:<br>
`PCPokktAds::checkRewardedVideoAdAvailability(screenName)`

**Note:-**<br>
**ScreenName:** A screen-name acts as a placement-id for ads. This is configured via Pokkt dashboard. Any request for ad has to refer a configured screen-name, Default
value of screenname is “Default”

#####Non Rewarded
1. Cache NonRewarded Ad:<br>
`PCPokktAds::cacheNonRewardedVideoAd(screenName)`<br>

2. Show NonRewarded Ad:<br>
`PCPokktAds::showNonRewardedVideoAd(screenName)`<br>

3. Check Ad Availability Status:<br>
`PCPokktAds::checkNonRewardedVideoAdAvailability(screenName)`<br>

**Note:-** <br>
**ScreenName:** A screen-name acts as a placement-id for ads. This is configured
via Pokkt dashboard. Any request for ad has to refer a configured screen-name, Default value of screenname is “Default”

####Interstitial
#####Rewarded
1. Cache Rewarded Ad:<br>
`PCPokktAds::cacheRewardedInterstitialAd(screenName)`

2. Show Rewarded Ad:<br>
`PCPokktAds::showRewardedInterstitialAd(screenName)`

3. Check Ad Availability Status:
`PCPokktAds::checkRewardedInterstitialAdAvailability(screenName)`

**Note:-**<br> 
**ScreenName:** A screen-name acts as a placement-id for ads. This is configured via Pokkt dashboard. Any request for ad has to refer a configured screen-name, Default value of screenname is “Default”

#####Non Rewarded
1. Cache Non Rewarded Ad:<br>
`PCPokktAds::cacheNonRewardedInterstitialAd(screenName)`
2. Show Non Rewarded Ad:<br>
`PCPokktAds::showNonRewardedInterstitialAd(screenName)`
3. Check Ad Availability Status:<br>
`PCPokktAds::checkNonRewardedInterstitialAdAvailability(screenName)`

**Note:-** 
ScreenName: A screen-name acts as a placement-id for ads. This is configured
via Pokkt dashboard. Any request for ad has to refer a configured screen-name, Default
value of screenname is “Default”

####Banner
#####1. Banner Initialization: 
You can load banner with two types:<br>
● You will have to call PCPokktAds::loadBanner(screenName, position) to show banner on device. You will have to set the following for requesting to load banner:

**a) Screen Name :** A screen-name acts as a placement-id for banner ads. This is configured via Pokkt dashboard. Any request for banner ad has to refer a configured
screen-name. Following image explains the configuration process of a screen-name on Pokkt dashboard.

**b) Position :** This is a predefined location where you would like to place your banner, all possible values are defined in BannerPosition enum. You can select one as per
your placement requirement. Possible values are:

~~~
TopLeft
TopCenter
TopRight
MiddleLeft
MiddleRight
BottomLeft
BottomCenter
BottomRight
~~~
● Alternatively, you can call below method for a custom positioning of your banner

`PCPokktAds::initWithBannerAdSize(screenName, height, width, x, y)`<br>

#####2. Refresh Banner
`PCPokktAds::setBannerAutoRefresh(shouldAutoRefresh)`

#####3. Destroy Banner
`PCPokktAds::destroyBanner()`

**Note:-** 
**ScreenName:** A screen-name acts as a placement-id for ads. This is configured via Pokkt dashboard. Any request for ad has to refer a configured screen-name, Default
value of screenname is “Default”

##Ad Listener
Ad Listner are optional, but we suggest to implement them as it will help you to keep track of the status of your ad request.

###Video

~~~
PCPokktAds::setAdEventListener(AD_AVAILABILITY_EVENT,
PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdAvailability), this);
PCPokktAds::setAdEventListener(AD_CACHING_COMPLETED_EVENT,PC_ADS_EVENT_SELECTO
R(VideoAdsView::handleAdCachingCompleted), this);
PCPokktAds::setAdEventListener(AD_CACHING_FAILED_EVENT,
PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdCachingFailed), this);
PCPokktAds::setAdEventListener(AD_DISPLAYED_EVENT,
PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdDisplayed), this);
PCPokktAds::setAdEventListener(AD_SKIPPED_EVENT,
PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdSkipped), this);
PCPokktAds::setAdEventListener(AD_COMPLETED_EVENT,
PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdCompleted), this);
PCPokktAds::setAdEventListener(AD_CLOSED_EVENT,
PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdClosed), this);
PCPokktAds::setAdEventListener(AD_GRATIFIED_EVENT,
PC_ADS_EVENT_SELECTOR(VideoAdsView::handleAdGratified), this);
~~~

###Interstitial

~~~
PCPokktAds::setAdEventListener(AD_AVAILABILITY_EVENT,
PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdAvailability), this);
PCPokktAds::setAdEventListener(AD_CACHING_COMPLETED_EVENT,PC_ADS_EVENT_SELECT
OR(InterstitialAdsView::handleAdCachingCompleted), this);
PCPokktAds::setAdEventListener(AD_CACHING_FAILED_EVENT,PC_ADS_EVENT_SELECTOR(Int
erstitialAdsView::handleAdCachingFailed), this);
PCPokktAds::setAdEventListener(AD_DISPLAYED_EVENT,
PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdDisplayed), this);
PCPokktAds::setAdEventListener(AD_SKIPPED_EVENT,
PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdSkipped), this);
PCPokktAds::setAdEventListener(AD_COMPLETED_EVENT,
PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdCompleted), this);
PCPokktAds::setAdEventListener(AD_CLOSED_EVENT,
PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdClosed), this);
PCPokktAds::setAdEventListener(AD_GRATIFIED_EVENT,
PC_ADS_EVENT_SELECTOR(InterstitialAdsView::handleAdGratified), this);
~~~

###Banner

~~~
PCPokktAds::setAdEventListener(BANNER_LOADED_OP,
PC_ADS_EVENT_SELECTOR(BannerAdsView::handleBannerLoadSuccessfuly), this);
PCPokktAds::setAdEventListener(BANNER_LOAD_FAILED_OP,
PC_ADS_EVENT_SELECTOR(BannerAdsView::handleBannerLoadFailed), this);
~~~

##Pokkt ad player configuration

You can configure an PokktAdPlayerViewConfig object to request for any ad to be displayed. It also provides options for customizing your ad-screen. It is recommended to have different PokktAdPlayerViewConfig objects for each screens. Followings are the values that you can set with PokktAdPlayerConfig :

~~~
PokktAdPlayerViewConfig adPlayerViewConfig = new PokktAdPlayerViewConfig ();
// set properties values to adPlayerViewConfig
PCPokktAds::setAdPlayerViewConfig(adPlayerViewConfig);
~~~
● **defaultSkipTime :** If ad-skipping is allowed, this provides the seconds it will wait before
the skip button appears.<br>
● **shouldAllowSkip :** Whether skipping-ad is allowed or not. If set to ‘false’, user will be forced to watch the ad till it finishes.<br>
● **shouldAllowMute :** Whether to allow sound-mute while on ad-screen, it controls the ‘mute’ button. Cannot contains whitespaces and only special characters allowed are
hyphens (-) and underscores (_).<br>
● **shouldConfirmSkip :** Controls whether to show the skip-confirmation dialog box. If set to ‘false’, the ad will be silently closed without prompting for confirmation<br>
● **skipConfirmMessage :** The message that will appear on skip-confirmation dialog box.<br>
● **skipConfirmYesLabel :** ‘Yes’ Label of skip-confirmation dialog box.<br>
● **skipConfirmNoLabel :** ‘No’ Label of skip-confirmation dialog box.<br>
● **skipTimerMessage :** The message on countdown-timer before the skip button appears. The message must contain a ‘##’-placeholder to show timer value.<br>
● **incentiveMessage :** If set, the message will be displayed while prompting user to watch
the ad for certain time before it can be rewarded.

##AnalyticsWe support various analytics in Pokkt SDK.Below is mentioned how to enable various analytics with Pokkt SDK.
###Google AnalyticsGoogle analytics Id can be obtained from Google dashboard.

~~~AnalyticsDetails analyticsDetail = new AnalyticsDetails();analyticsDetail.setSelectedAnalyticsType( AnalyticsType.GOOGLE_ANALYTICS);analyticsDetail.setGoogleAnalyticsID( "<Google Analytics Id>");PCPokktAds::setAnalyticDetail(analyticsDetail);
~~~###Flurry AnalyticsFlurry application key can be obtained from Flurry dashboard.

~~~AnalyticsDetails analyticsDetail = new AnalyticsDetails();analyticsDetail.setSelectedAnalyticsType( AnalyticsType.FLURRY);analyticsDetail.setFlurryApplicationKey("<Flurry Application Key>");PCPokktAds::setAnalyticDetail(analyticsDetail);
~~~
###MixPanel AnalyticsMixPanel project token can be obtained from MixPanel dashboard.

~~~AnalyticsDetails analyticsDetail = new AnalyticsDetails();analyticsDetail.setSelectedAnalyticsType(AnalyticsType.MIXPANEL);analyticsDetail.setMixPanelProjectToken( "<MixPanel Project Token>");PCPokktAds::setAnalyticDetail(analyticsDetail);
~~~###Fabric AnalyticsAnalytics Id is not required in case of Fabric.

~~~AnalyticsDetails analyticsDetail = new AnalyticsDetails();analyticsDetail.setSelectedAnalyticsType(AnalyticsType.FABRIC);PCPokktAds::setAnalyticDetail(analyticsDetail);
~~~##IAP(In App Purchase)Call trackIAP to send any In App purchase information to Pokkt.

~~~InAppPurchaseDetails inAppPurchaseDetails = new InAppPurchaseDetails();inAppPurchaseDetails.setProductId("<productId>");inAppPurchaseDetails.setPurchaseData("<purchaseData>");inAppPurchaseDetails.setPurchaseSignature("<purchaseSignature>");inAppPurchaseDetails.setPurchaseStore(IAPStoreType.GOOGLE);inAppPurchaseDetails.setPrice(<100.00>);PCPokktAds::setTrackIAP(inAppPurchaseDetails);
~~~


##Debugging
Other than enabling debugging for Pokkt SDK, it can also be used to:<br>
1. Export log
`PCPokktAds::exportLog();`
