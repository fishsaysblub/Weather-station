#include "unity.h"
#include "WIFI_TESTS.h"

WIFI_TESTS::WIFI_TESTS()
{
}

void WIFI_TESTS::Test_Initialise()
{
    WIFI_TESTS tests = WIFI_TESTS::GetInstance();
    tests._Wifi = Wifi();
    tests._Wifi.InitializeNVS();
    TEST_ASSERT_TRUE(true);
}