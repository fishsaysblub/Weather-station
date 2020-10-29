#ifndef UNIT_TEST

extern "C" void app_main();

#include "WeatherStation.h"

#include "Sensor.h"
void app_main(void)
{
    WeatherStation station = WeatherStation();
    station.Start();
}


#endif