#pragma once

#include "esp_http_client.h"
#include <string.h>
#include "Data.h"

class HTTPClient 
{
    private:
        esp_http_client_config_t _config;
        void InitHTTPClientConfig(esp_http_client_config_t *config);
        static esp_err_t EventHandler(esp_http_client_event_t *evt);

    public:
        HTTPClient();
        void PostData(Data data);
};