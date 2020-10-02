#include "HTTPClient.h"

#include <string.h>

HTTPClient::HTTPClient() { InitHTTPClientConfig(&_config); }

void HTTPClient::InitHTTPClientConfig(esp_http_client_config_t *config)
{
    memset(config, 0, sizeof(*config));
    config->url = "http://192.168.1.5/SS_Project-5/data.php/";
    config->method = HTTP_METHOD_POST;
    config->event_handler = EventHandler;
}

int HTTPClient::PostData(Data data)
{
    // Preperation of POST
    esp_http_client_handle_t client = esp_http_client_init(&_config);
    ESP_ERROR_CHECK(esp_http_client_set_header(client, "Content-Type", "application/json"));

    char buffer[MAX_POST_SIZE];
    data.GetPost(buffer);
    ESP_ERROR_CHECK(esp_http_client_set_post_field(client, buffer, strlen(buffer)));

    //Sending of data.
	esp_err_t err = PerformPost(&client);

    // Cleanup and error checks
    ESP_ERROR_CHECK(err);    
    ESP_ERROR_CHECK(esp_http_client_close(client));
	ESP_ERROR_CHECK(esp_http_client_cleanup(client));
    return ESP_OK;
}

esp_err_t HTTPClient::PerformPost(esp_http_client_handle_t *client)
{

    esp_err_t err = esp_http_client_perform((*client));

#ifdef DEBUG
	if (err == ESP_OK) 
    {
		int resp_len = esp_http_client_get_content_length((*client));

        printf("HTTP POST Status = %d, content_length = %d", 
            esp_http_client_get_status_code((*client)),
			resp_len);

        return ESP_OK;
	}

    printf("HTTP POST request failed: %s", esp_err_to_name(err));
#endif
    return err;
}

esp_err_t HTTPClient::EventHandler(esp_http_client_event_t *evt)
{
    if(evt->event_id == HTTP_EVENT_ON_DATA)
    {
        printf("got data in handler: %d\n", evt->data_len);
        printf("buffer: %s", (char*)evt->data);
    }
    return ESP_OK;
}