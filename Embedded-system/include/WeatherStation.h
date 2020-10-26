#pragma once

#include "HTTPClient.h"
#include "Wifi.h"
#include "Sensor.h"

#include "esp_sleep.h"
#include "esp_pm.h"


#define MAIN_TASK_TAG "Main Task"
#define WIFI_TASK_TAG "Wifi Task"
#define SENSOR_TASK_TAG "Sensory Task"

#define SENSOR_READ_BIT BIT0
#define DATA_POSTED_BIT BIT1
#define FAILURE_BIT BIT2

#define MIN_CPU_FREQ_MHZ 10
#define MAX_CPU_FREQ_MHZ 80

class WeatherStation
{
    // ESP CONFIG
private:
    void SetESPConfig();

// TASKS
private:
    void AwaitRoutine();
    static void WifiTask(void *arg);
    static void SensorTask(void *arg);

// Private methods.
private:
    void SendData();
    void Sleep();

public:
    WeatherStation();
    void Start();
    void InitialiseConnectivity();
    void ReadSensoryData();
    virtual ~WeatherStation();

private:
    Wifi _WifiClient;
    HTTPClient _HTTPClient;
    Sensor _Sensors;

};

enum TaskPriority
{
    PRIORITY_IDLE = tskIDLE_PRIORITY,
    PRIORITY_LOW = 1,
    PRIORITY_MID = 2,
    PRIORITY_HIGH = 4
};

