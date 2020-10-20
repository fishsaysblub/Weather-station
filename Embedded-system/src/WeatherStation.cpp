#include "WeatherStation.h"

static EventGroupHandle_t s_event_group;

TaskHandle_t WifiTaskHandle;
TaskHandle_t SensorTaskHandle;

WeatherStation* s_Instance = nullptr;

WeatherStation::WeatherStation() : 
_WifiClient(Wifi()), _HTTPClient(HTTPClient())
{
    s_event_group = xEventGroupCreate();

    WifiTaskHandle = NULL;
    SensorTaskHandle = NULL;
    s_Instance = this;

    SetESPConfig();
}

void WeatherStation::SetESPConfig()
{
    esp_pm_config_esp32_t config;
    config.light_sleep_enable = true;
    config.min_freq_mhz = MIN_CPU_FREQ_MHZ;
    config.max_freq_mhz = MAX_CPU_FREQ_MHZ;
    ESP_ERROR_CHECK(esp_pm_configure((void*)(&config)));
}

void WeatherStation::Start()
{
    xTaskCreate(WifiTask, WIFI_TASK_TAG, 4096, NULL, PRIORITY_MID, &WifiTaskHandle);
    xTaskCreate(SensorTask, SENSOR_TASK_TAG, 2048, NULL, PRIORITY_MID, &SensorTaskHandle);
    AwaitRoutine();
}

void WeatherStation::AwaitRoutine()
{
    EventBits_t bits =  xEventGroupWaitBits(
        s_event_group,
        DATA_POSTED_BIT | FAILURE_BIT,
        pdFALSE,
        pdFALSE,
        portMAX_DELAY
    );

    LOGGER("Got past await");
    if(bits & FAILURE_BIT)
    {
        LOGGER("Unexpected failure");
    }

    if(bits & DATA_POSTED_BIT)
    {
        LOGGER("Should enter sleep modi.");
    }
    Sleep();
}

void WeatherStation::WifiTask(void *arg)
{
    while(1)
    {
        s_Instance->InitialiseConnectivity();

        xEventGroupWaitBits(
            s_event_group,
            SENSOR_READ_BIT,
            pdTRUE,
            pdTRUE,
            portMAX_DELAY
        );

        //_HTTPClient.PostData(_Sensors.GetData());       
        s_Instance->SendData(); // This is a placeholder function call.
        xEventGroupSetBits(s_event_group, DATA_POSTED_BIT);     
        vTaskDelay(10000 / portTICK_RATE_MS);
    }
}

void WeatherStation::SensorTask(void *arg)
{
    while(1)
    {
        s_Instance->InitialiseSensors();
        //_Sensors.ReadSensors();
        xEventGroupSetBits(s_event_group, SENSOR_READ_BIT);
        vTaskDelay(10000 / portTICK_RATE_MS);
    }
}

void WeatherStation::InitialiseConnectivity()
{
    static bool isInitialised = false;

    if(isInitialised == true)
        return;
   
    int success = _WifiClient.InitializeWifi();

    if(success)
        LOGGER("Woo");
    else
        LOGGER("Not wooo");

    if(!success)
        return;
}
void WeatherStation::InitialiseSensors()
{
    LOGGER("No sensors");
}

void WeatherStation::SendData()
{
    Data data;
    memset(&data, 0, sizeof(Data));
    data.Humidity = 34;
    data.Temperature = 52;
    
    int result = _HTTPClient.PostData(data);
    if(result == ESP_OK)
    {
        LOGGER("is ok");
    }
    if(result == ESP_FAIL)
    {
        xEventGroupSetBits(s_event_group, FAILURE_BIT);
    }

}

WeatherStation::~WeatherStation()
{
    vEventGroupDelete(s_event_group);

    if(WifiTaskHandle != NULL)
        vTaskDelete(WifiTaskHandle);

    if(SensorTaskHandle != NULL)
        vTaskDelete(SensorTaskHandle);
}

void WeatherStation::Sleep()
{
    LOGGER("Entering sleep mode...\n");
    _WifiClient.Sleep();
    esp_sleep_enable_timer_wakeup(57000000);
    esp_deep_sleep_start();
    
    //_Sensors.Sleep();

    // Start wakeup routine
}