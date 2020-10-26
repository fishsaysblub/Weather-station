#pragma once

#include <cstdint>

class sensor
{
private:
    bool rh_measurment = false;
   
public:
    sensor();

    uint8_t readFirmware();
    uint16_t readTemperature();
    uint16_t readHumidity();
    
    int test;

};







