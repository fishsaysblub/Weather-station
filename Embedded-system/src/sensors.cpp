#include "sensors.h"
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

    uint16_t humidity = temp[0] << 8 | temp[1];
    float calculatedHum = (((175.72 * humidity) / 65536.0) - 46.85);

    printf("Temp reading: %f\n", calculatedHum);

    return 0;
}

uint16_t sensor::readHumidity()
{
    const uint8_t cmd_read_hum[] = {0xE5};
    uint8_t hum[2];

    i2c_command.writeCmd(si7021_address, (uint8_t *)cmd_read_hum, 1);
    vTaskDelay(100 / portTICK_RATE_MS);
    i2c_command.readCmd(si7021_address, (uint8_t *)cmd_read_hum, 1, hum, 2);

    uint16_t temperature = hum[0] << 8 | hum[1];
    float calculatedTemp = (((125.0 * temperature) / 65536.0) - 6.0);

    printf("Humidity reading: %f\n", calculatedTemp);

    return 0;
}
