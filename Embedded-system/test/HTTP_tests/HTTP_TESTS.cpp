#include "unity.h"

extern "C" void app_main();

void test_initialisation();
void test_config();

void app_main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_initialisation);
    test_config();

    UNITY_END();
};

void test_initialisation()
{
    bool as = true;
    TEST_ASSERT_TRUE(as);
}

void test_config()
{
    
    /*wifi_config_t *config;
    memset(config, 0, sizeof(*config));       
    strcpy((char *) config->sta.ssid, "NETGEAR18");
    strcpy((char *) config->sta.password, "wittycheese610");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, config));

    TEST_ASSERT_EQUAL_STRING("NETGEAR18", config->sta.ssid);
    TEST_ASSERT_EQUAL_STRING("wittycheese610", config->sta.password);

    wifi_mode_t mode;
    esp_wifi_get_mode(&mode);
    TEST_ASSERT_EQUAL_INT16(WIFI_MODE_STA, mode);*/
}