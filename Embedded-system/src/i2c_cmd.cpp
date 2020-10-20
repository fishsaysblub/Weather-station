#include "i2c_cmd.h"
#include <iostream>

static gpio_num_t i2c_gpio_sda = GPIO_NUM_21;
static gpio_num_t i2c_gpio_scl = GPIO_NUM_22;
static uint32_t i2c_frequency = 100000;
static i2c_port_t i2c_port = I2C_NUM_0;

i2c_cmd::i2c_cmd()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = i2c_gpio_sda;
    conf.scl_io_num = i2c_gpio_scl;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = i2c_frequency;

    i2c_param_config(i2c_port, &conf);

    i2c_driver_install(i2c_port, I2C_MODE_MASTER, 0, 0, 0);

    std::cout << "i2c config finished" << std::endl;
    // init i2c bus and handles
}

void i2c_cmd::writeCmd(uint8_t address, uint8_t *data, uint8_t data_len)
{
    if (data_len && *data) // if datalen > 0 && *data != null
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1 | I2C_MASTER_WRITE), I2C_MASTER_ACK); // Slave address

        for (int i = 0; i < data_len; i++)
        {
            i2c_master_write_byte(cmd, data[i], I2C_MASTER_ACK);
        }

        i2c_master_stop(cmd);
        i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(cmd);
    }
    else
    {
        {
            std::cout << "Incorrect arguments in writeCmd()" << std::endl;
        }
    }
}

void i2c_cmd::readCmd(uint8_t address, uint8_t *data_cmd, uint8_t data_cmd_len, uint8_t *read_data, uint8_t read_data_len)
{
    if (data_cmd_len && *data_cmd) // if datalen > 0 && *data != null
    {
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();

        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (address << 1 | I2C_MASTER_READ), I2C_MASTER_ACK); // Write the address to the slave to read.

        for (int i = 0; i < read_data_len; i++)
        {
            i2c_master_read_byte(cmd, &read_data[i], i == read_data_len - 1 ? I2C_MASTER_NACK : I2C_MASTER_ACK);
        }

        i2c_master_stop(cmd);
        i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
        i2c_cmd_link_delete(cmd);
    }
    else
    {
        {
            std::cout << "Incorrect arguments in readCmd()" << std::endl;
        }
    }
}
