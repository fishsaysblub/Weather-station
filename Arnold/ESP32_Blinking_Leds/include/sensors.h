#pragma once

#include <cstdint>
#include "driver/i2c.h"

/* Command table */
//const 


class sensor
{
    private:
    int16_t readHumidity;
    int16_t readTemperature;

    public:
    sensor();

    uint8_t readFirmware();

    int test;

};







