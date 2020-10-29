#ifndef __IC2_H
#define __IC2_H

#include "driver/i2c.h"
#include <CMDData.h>

#define FAST_I2C 400000
#define DEF_92C 100000

class I2C
{
private:
    void InitI2CConfig(i2c_config_t * config);
    void Initialise(i2c_config_t * config);
    void Start(i2c_cmd_handle_t * cmd_handle, uint8_t address, i2c_rw_t rw);
    void Reset(i2c_cmd_handle_t * cmd);
    
public:
    I2C();

public:
    void WriteCmd(CMDData * cmd);
    void ReadCmd(CMDData * cmd);
};


#endif