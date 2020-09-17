extern "C" void app_main();

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include <stdio.h>
#include <iostream>

#include "Wifi.h"
#include "HTTPClient.h"

void InitializeNVS();

void app_main(void)
{

    InitializeNVS();

    Wifi wifi = Wifi();
    int success = wifi.InitializeWifi();
    if(success)
        LOGGER("Woo");
    else
        LOGGER("Not wooo");

    if(!success)
        return;
    
    HTTPClient client = HTTPClient();
    client.PostData();
}

void InitializeNVS()
{
    // Initialize non-volatile storage
    esp_err_t ret = nvs_flash_init();
    if (ret == (ESP_ERR_NVS_NO_FREE_PAGES || ESP_ERR_NVS_NEW_VERSION_FOUND))
    {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
}