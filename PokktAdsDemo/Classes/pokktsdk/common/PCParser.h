#ifndef PCParser_h
#define PCParser_h

#include <map>
#include "PCPokktConfig.h"
#include "IAPDetails.h"
#include "../cajun/json/writer.h"
#include "../cajun/json/reader.h"
#include "../cajun/json/elements.h"


using namespace pokkt;


std::string toIAPDetailsJSONString(IAPDetails* details);
std::string toBannerParamsJSONString(std::string screenName, int bannerPosition);
std::string toBannerRectParamsJSONString(std::string screenName,  int width, int height, int x, int y);

#endif /* PCParser_h */
