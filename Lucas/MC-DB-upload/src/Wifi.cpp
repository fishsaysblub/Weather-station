#include "Wifi.h"

static int s_retry_num = 0;
static EventGroupHandle_t s_wifi_event_group;

Wifi::Wifi()
{
    s_wifi_event_group = xEventGroupCreate();

    ESP_ERROR_CHECK(esp_netif_init());

    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    ESP_ERROR_CHECK(esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &EventHandler, NULL));
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &EventHandler, NULL));
}

void Wifi::EventHandler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data)
{
    if(event_base == WIFI_EVENT)
        HandleWifiEvent(event_id);

    if (event_base != IP_EVENT || event_id != IP_EVENT_STA_GOT_IP) 
        return;
    
    s_retry_num = 0;
    xEventGroupSetBits(s_wifi_event_group, WIFI_CONNECTED_BIT);   
}

void Wifi::HandleWifiEvent(int32_t event_id)
{
    if(event_id == WIFI_EVENT_STA_START)
    {
        esp_wifi_connect();
        return;
    }

    if (s_retry_num < ESP_MAXIMUM_RETRY) 
    {
        esp_wifi_connect();
        s_retry_num++;
        
        LOGGER("Retrying to connect to wifi.");
        return;
    } 
    
    xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
    LOGGER("Failed to establish a wifi connection.");
}

int Wifi::InitializeWifi()
{
    wifi_config_t wifi_config;
    InitWifiConfig(&wifi_config);
    ESP_ERROR_CHECK(esp_wifi_start());
    
    AwaitConnection();

    ESP_ERROR_CHECK(esp_event_handler_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, &EventHandler));
    ESP_ERROR_CHECK(esp_event_handler_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, &EventHandler));

    EventBits_t bits = xEventGroupGetBits(s_wifi_event_group);
    int status = (bits & WIFI_CONNECTED_BIT);
    vEventGroupDelete(s_wifi_event_group);
    LOGGER("Finished wifi routine.");  
    return status;
}

void Wifi::InitWifiConfig(wifi_config_t *config)
{
    memset(config, 0, sizeof(*config));       
    strcpy((char *) config->sta.ssid, "NETGEAR18");
    strcpy((char *) config->sta.password, "wittycheese610");
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, config));
}

void Wifi::AwaitConnection()
{
    // These bits are used for error checking.
    // They are set in the method 'EventHandler'
    EventBits_t bits = xEventGroupWaitBits
    (
        s_wifi_event_group,
        WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );

    if (bits & WIFI_CONNECTED_BIT) 
    {    
        LOGGER("Established wifi connection.");  
        return;
    } 
    else if (bits & WIFI_FAIL_BIT) 
    {
        LOGGER("Failed to connect to wifi, check credentials and password.");
        return;
    } 

    LOGGER("Unexpected failure.");
}