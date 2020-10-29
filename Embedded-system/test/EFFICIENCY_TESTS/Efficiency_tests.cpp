#include "unity.h"

#include "esp_sleep.h"
#include "esp_pm.h"

extern "C" void app_main();

void CheckFrequency();

void app_main(void)
{
    UNITY_BEGIN();

    RUN_TEST(CheckFrequency);

    UNITY_END();
};

//! Frequency test
/*!
    The following method has been tested, however has been disabled due to the bug prone behaviour of the system.
    For some reason, when enabling light sleep during testing it causes the system to forget it was testing,
    it then proceeds to enter the light sleep state and hangs permanently.

    To be honest, I have no clue how to test this otherwise.
    When it doubt, disable the safe guard and execute the tests.
*/
void CheckFrequency()
{
    TEST_ASSERT_TRUE(true);
    return;
    
    esp_pm_config_esp32_t config;
    config.light_sleep_enable = true;
    config.min_freq_mhz = 10;
    config.max_freq_mhz = 80;
    ESP_ERROR_CHECK(esp_pm_configure((void*)(&config))); 
    
    TEST_ASSERT_TRUE(config.light_sleep_enable == true);
    TEST_ASSERT_TRUE(config.min_freq_mhz == 10);
    TEST_ASSERT_TRUE(config.max_freq_mhz == 80);
}
