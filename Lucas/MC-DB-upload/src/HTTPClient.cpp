#include "HTTPClient.h"

const char *post_data = "{\"temp\":\"7\"}";

esp_err_t EventHandler(esp_http_client_event_t *evt);

HTTPClient::HTTPClient()
{
    InitHTTPClientConfig(&_config);
}

void HTTPClient::InitHTTPClientConfig(esp_http_client_config_t *config)
{
    memset(config, 0, sizeof(*config));
    config->url = "http://192.168.1.5/SS_Project-5/data.php/";
    config->method = HTTP_METHOD_POST;
    config->event_handler = EventHandler;
}

void HTTPClient::PostData()
{
    esp_http_client_handle_t client = esp_http_client_init(&_config);
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, post_data, strlen(post_data));

	esp_err_t err = esp_http_client_perform(client);
	if (err == ESP_OK) 
    {
		int resp_len = esp_http_client_get_content_length(client);

        printf("HTTP POST Status = %d, content_length = %d", 
            esp_http_client_get_status_code(client),
			resp_len);
	}
	else 
    {
         printf("HTTP POST request failed: %s", esp_err_to_name(err));
	}
    esp_http_client_close(client);
	esp_http_client_cleanup(client);
    return;
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