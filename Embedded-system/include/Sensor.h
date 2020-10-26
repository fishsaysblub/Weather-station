#ifndef __SENSOR_H
#define __SENSOR_H

// I2C Address of the sensor.
#define SI7021_ADDRESS 0x40
#define TEMPERATURE_BYTE 0xF3
#define HUMIDITY_BYTE 0xE5

#include "I2C.H"
#include "Data.h"

class Sensor
{
private:
    I2C _I2C;
    Data * _Data;

public:
    Sensor();
    virtual ~Sensor();

public:
    void ReadSensors();
    const Data& GetData() const;

private:
    float ReadTemperature();
    float ReadHumidity();
    void ReadI2C(uint8_t* buffer, CMDData * data);
    void ConfigureCMD(CMDData * data, uint8_t* buffer, const int output_len);
};


#endif