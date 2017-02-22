#include "PCAndroidExtension.h"
#include "../pokkt.h"
#include "../../pokktsdk/common/PCPokktAds.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"

using namespace pokkt;


#ifdef __cplusplus
extern "C"
{
#endif
    
    /**
     * HANDLES NATIVE ANDROID MESSAGES
     **/
    void Java_com_pokkt_plugin_PokktNativeExtension_notifyFramework(JNIEnv* env, jobject thiz, jstring operation, jstring param)
    {
        std::string operationString = cocos2d::JniHelper::jstring2string(operation);
        std::string paramString = cocos2d::JniHelper::jstring2string(param);
        
        pokkt::PCPokktAds::handleNativeMessage(operationString, paramString);
        
        env->DeleteLocalRef(operation);
        env->DeleteLocalRef(param);
    }

#ifdef __cplusplus
};
#endif

void notifyAndroid(std::string operation, std::string param)
{
	POKKTLOG("[POKKT-CPP] notifying android of operation: %s, param: %s", operation.c_str(), param.c_str());

	cocos2d::JniMethodInfo methodInfo;
	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
												 "com/pokkt/plugin/PokktNativeExtension",
												 "notifyNative",
												 "(Ljava/lang/String;Ljava/lang/String;)V"))
		return;

	jstring joperation = methodInfo.env->NewStringUTF(operation.c_str());
	jstring jparam = methodInfo.env->NewStringUTF(param.c_str());
	methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, joperation, jparam);

	methodInfo.env->DeleteLocalRef(methodInfo.classID);
	methodInfo.env->DeleteLocalRef(joperation);
	methodInfo.env->DeleteLocalRef(jparam);
}

std::string getSDKVersionOnAndroid()
{
	POKKTLOG("[POKKT-CPP] checking for sdk version on android device...");

	cocos2d::JniMethodInfo methodInfo;
	if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
												 "com/pokkt/plugin/PokktNativeExtension",
												 "getSDKVersionOnNative",
												 "()Ljava/lang/String;"))
		return "not-found";

	jstring jresult = (jstring) methodInfo.env->CallStaticObjectMethod(methodInfo.classID, methodInfo.methodID);
	std::string result = cocos2d::JniHelper::jstring2string(jresult);

	methodInfo.env->DeleteLocalRef(methodInfo.classID);
	methodInfo.env->DeleteLocalRef(jresult);

	POKKTLOG("[POKKT-CPP] sdk version on android deivce currently is %s!", result.c_str());

	return result;
}

#endif
