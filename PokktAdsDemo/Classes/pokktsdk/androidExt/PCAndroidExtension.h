#ifndef AndroidExtension_h
#define AndroidExtension_h

#include <string>

void notifyAndroid(std::string operation, std::string param = "");
std::string getSDKVersionOnAndroid();

#endif /* AndroidExtension_h */
