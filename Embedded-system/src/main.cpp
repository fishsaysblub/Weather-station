extern "C" void app_main();

#include "WeatherStation.h"

void app_main(void)
{
    WeatherStation station = WeatherStation();
    station.Start();
}