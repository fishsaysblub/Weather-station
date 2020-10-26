#include "unity.h"
#include "WIFI_TESTS.h"

extern "C" void app_main();

void app_main(void)
{
    UNITY_BEGIN();

    //RUN_TEST(WIFI_TESTS::Test_Initialise);

    UNITY_END();
};
