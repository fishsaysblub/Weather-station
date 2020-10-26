#pragma once

#include <cstdint>
#include "driver/i2c.h"

class i2c_cmd
{
private:

public:
    i2c_cmd();

    void writeCmd(uint8_t address, uint8_t *data, uint8_t data_len);
    void readCmd(uint8_t address, uint8_t *data_cmd, uint8_t data_cmd_len, uint8_t *read_data, uint8_t read_data_len);
};

