//#ifdef UNIT_TEST

extern "C" void app_main();

#include "WeatherStation.h"

#include "Sensor.h"
void app_main(void)
{
    /*
    Sensor sensor;
    sensor.ReadSensors();
    Data data = sensor.GetData();
    printf("temp %f\n", data.Temperature);
    printf("hum %f\n", data.Humidity);
    return;
    */
    WeatherStation station = WeatherStation();
    station.Start();
}


//#endif