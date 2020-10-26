#ifndef __WIFI_TESTS_H
#define __WIFI_TESTS_H

#include "Wifi.h"

class WIFI_TESTS
{
private:
    WIFI_TESTS();
    Wifi _Wifi;
    
public:
    static void Test_Initialise();

public:
    static inline WIFI_TESTS& GetInstance() 
    {
         static WIFI_TESTS s_Wifi_tests = WIFI_TESTS();
         return s_Wifi_tests;
    };
};

#endif