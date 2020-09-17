#pragma once

#include <cstdint>
#include "driver/i2c.h"

/* Command table */
//const 


class sensor
{
    private:
    int16_t readHumidity;
   
    public:
    sensor();

    uint8_t readFirmware();
    uint16_t readTemperature();
    int test;

};







