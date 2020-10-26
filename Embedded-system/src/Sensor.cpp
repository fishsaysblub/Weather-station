#include "Sensor.h"

Sensor::Sensor() : _I2C(I2C()), _Data(nullptr) { }

void Sensor::ReadSensors()
{
    if(_Data == nullptr)
        _Data = new Data();

    _Data->Temperature = ReadTemperature();
    _Data. = ReadHumidity();
}

float Sensor::ReadTemperature()
{
    CMDData data;
    uint8_t data_buffer[] = {TEMPERATURE_BYTE};
    ReadI2C(data_buffer, &data);

    uint16_t temp = data.OutputBuffer[0] << 8 | data.OutputBuffer[1];
    float temperature = ((175.72 * temp) / 65536.0) - 46.85;
    
    return temperature;
}

float Sensor::ReadHumidity()
{
    CMDData data;
    uint8_t data_buffer[] = {HUMIDITY_BYTE};
    ReadI2C(data_buffer, &data);

    uint16_t hum = data.OutputBuffer[0] << 8 | data.OutputBuffer[1];
    float humidity = (((125.0 * hum) / 65536.0) - 6.0);

    return humidity;
}

void Sensor::ReadI2C(uint8_t* buffer, CMDData * data)
{
    ConfigureCMD(data, buffer, 2);

    _I2C.WriteCmd(data);
    vTaskDelay(100 / portTICK_RATE_MS);
    _I2C.ReadCmd(data);
}

void Sensor::ConfigureCMD(CMDData * data, uint8_t* buffer, const int output_len)
{
    data->Address = SI7021_ADDRESS;
    data->Buffer = (uint8_t *)buffer;
    data->Len = sizeof(data) / sizeof(uint8_t);

    data->OutputBuffer = (uint8_t*)calloc(output_len, sizeof(uint8_t));
    data->OutputLen = output_len;
}

const Data& Sensor::GetData() const { return *_Data; }

Sensor::~Sensor()
{
    if(_Data != nullptr)
        delete _Data;
}