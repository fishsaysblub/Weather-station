extern "C" void app_main();

#include "Wifi.h"
#include "HTTPClient.h"
#include "Data.h"
#include <string.h>

void app_main(void)
{
    Wifi wifi = Wifi();
    int success = wifi.InitializeWifi();

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

    int result = client.PostData(data);
    if(result == ESP_OK)
        printf("is ok");
    else if(result == ESP_FAIL)
        printf("is not ok");
}