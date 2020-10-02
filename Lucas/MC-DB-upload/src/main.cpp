extern "C" void app_main();

#include "Wifi.h"
#include "HTTPClient.h"
#include "nvs_flash.h"
#include "Data.h"


void InitializeNVS();

void app_main(void)
{
    InitializeNVS();

    Wifi wifi = Wifi();
    int success = wifi.InitializeWifi();

    return;
    if(success)
        LOGGER("Woo");
    else
        LOGGER("Not wooo");

    if(!success)
        return;
    
    return;

    HTTPClient client = HTTPClient();

    Data data;
    memset(&data, 0, sizeof(Data));
    data.Humidity = 34;
    data.Temperature = 52;
    
    Data data2 = 
    {
        .Temperature = 34,
        .Humidity = 32
    };

    client.PostData(data);
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