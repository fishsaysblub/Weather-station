#pragma once

#include "esp_http_client.h"
#include "Data.h"

//! Wrapper for HTTP requests.
/*!
    Prepares and manages the HTTP client for sending data.
    Sends data to a predetirmened database through POST requests.
    For the data see: 
    \sa Data
*/
class HTTPClient 
{
    private:
        esp_http_client_config_t _config;

        //! Configures the HTTP instance.
        /*!
            Configure the HTTP config and attach event handler
            \param config HTTP config which should be initialised
            \sa esp_http_client_config_t
        */
        void InitHTTPClientConfig(esp_http_client_config_t *config);

        //! Performs the actual post.
        /*!
            Performs the post command and handles HTTP response.
            \param client HTTP client handle to send data towards, must be prepared.
            \returns error code, ESP_OK or ESP_FAIL.
        */
        esp_err_t PerformPost(esp_http_client_handle_t *client);
        //! Eventhandler for HTTP callbacks
        /*!  
            Set during initialisation in 
            \sa HTTPClient::InitHTTPClientConfig
        */
        static esp_err_t EventHandler(esp_http_client_event_t *evt);

    public:
        //! Prepares an HTTP instance for HTTP post requests
        /*!
            Prepares an HTTP instance for HTTP post requests.
            In order to post data construct a Data class and use PostData.
            \sa Data
            \sa  HTTPClient::PostData
        */
        HTTPClient();

        //! Posts the data within given Data struct to DB.
        /*!
            Posts the data within given Data struct to DB.
            \param data The data struct which data has to be posted.
            \returns Returns ESP_OK on succeed, ESP_FAIL on failure.
        */
        int PostData(Data data);
};