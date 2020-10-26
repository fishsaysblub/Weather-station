#include "sensors.h"

#include "i2c_cmd.h"
#include "I2C.H"
#include <stdlib.h>
#include <string.h>

i2c_cmd i2c_command;
I2C I2C_cmd;

static uint8_t si7021_address = 0x40; // Meegeven met sensorfunctie

sensor::sensor()
{
    // Nothing
}


void CreateCMDData(CMDData * data, uint8_t* buffer, const int output_len);

uint16_t sensor::readTemperature()
{
    CMDData data;
    uint8_t data_buffer[] = {0xF3};
    CreateCMDData(&data, data_buffer, 2);

    I2C_cmd.WriteCmd(&data);
    vTaskDelay(100 / portTICK_RATE_MS);
    I2C_cmd.ReadCmd(&data);

    uint16_t humidity = data.OutputBuffer[0] << 8 | data.OutputBuffer[1];
    float calculatedHum = ((175.72 * humidity) / 65536.0) - 46.85;
    printf("temp reading: %f\n", calculatedHum);
    return 0;
}


uint16_t sensor::readHumidity()
{
    return 0;
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


void CreateCMDData(CMDData * data, uint8_t* buffer, const int output_len)
{
    data->Address = si7021_address;
    data->Buffer = (uint8_t *)buffer;
    data->Len = sizeof(data) / sizeof(uint8_t);

    data->OutputBuffer = (uint8_t*)calloc(output_len, sizeof(uint8_t));
    data->OutputLen = output_len;
}