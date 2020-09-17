#pragma once

#include "esp_http_client.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event.h"
#include "esp_netif.h"
#include "esp_tls.h"

#include <stdio.h>
#include <iostream>
#include <string.h>

class HTTPClient 
{
    private:
        esp_http_client_config_t _config;
        void InitHTTPClientConfig(esp_http_client_config_t *config);
        static esp_err_t EventHandler(esp_http_client_event_t *evt);

    public:
        HTTPClient();
        void PostData();
};