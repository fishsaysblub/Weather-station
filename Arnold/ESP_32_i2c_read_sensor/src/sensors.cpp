#include "sensors.h"
#include <iostream>
#include <stdio.h>
#include "i2c_cmd.h"

i2c_cmd i2c_command;

static uint8_t si7021_address = 0x40; // Meegeven met sensorfunctie

sensor::sensor()
{
    // Nothing
}

uint16_t sensor::readTemperature()
{
    const uint8_t cmd_read_temp[] = {0xF3};
    uint8_t temp[2];

    i2c_command.writeCmd(si7021_address, (uint8_t *)cmd_read_temp, 1);
    vTaskDelay(100 / portTICK_RATE_MS);
    i2c_command.readCmd(si7021_address, (uint8_t *)cmd_read_temp, 1, temp, 2);

    uint16_t temperature = temp[0] << 8 | temp[1];
    float calculatedTemp = (((175.72 * temperature) / 65536.0) - 46.85);

    printf("Temp reading: %f\n", calculatedTemp);

    return 0;
}
