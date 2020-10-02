#pragma once

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"

#include "lwip/err.h"
#include "lwip/sys.h"

// Simple logger for information, not pretty, works fine.
#define LOGGER(log)(printf("Weather station: %s\n", log))

#define ESP_MAXIMUM_RETRY   5

#define WIFI_CONNECTED_BIT  BIT0
#define WIFI_CONNECTION_FAILED_BIT   BIT1

class Wifi
{

    private:    
        void InitWifiConfig(wifi_config_t *config);
        static void HandleWifiEvent(int32_t event_id);
        void AwaitConnection();
		static void EventHandler(void* arg, esp_event_base_t event_base, 
                                    int32_t event_id, void* event_data);

	public:
		Wifi();
		int InitializeWifi();
};


