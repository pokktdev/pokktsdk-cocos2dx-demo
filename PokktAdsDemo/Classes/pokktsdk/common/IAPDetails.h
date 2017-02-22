#ifndef IAPDetails_h
#define IAPDetails_h

#include <stdio.h>


namespace pokkt
{
    class IAPDetails
    {
    public:
        std::string productId;
        int price;
        std::string currencyCode;
        std::string title;
        std::string description;
        std::string purchaseData;
        std::string purchaseSignature;
        std::string purchaseStore;
    };
}

#endif /* IAPDetails_h */
