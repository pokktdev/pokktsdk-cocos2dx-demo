#ifndef PCPokktAnalyticsDetail_h
#define PCPokktAnalyticsDetail_h

#include <stdio.h>


namespace pokkt
{
    class PCPokktAnalyticsDetail
    {
    public:
        std::string googleTrackerID;
        std::string flurryTrackerID;
        std::string mixPanelTrackerID;
        std::string eventType;
    };
}

#endif /* IAPDetails_h */
