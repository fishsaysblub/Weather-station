#include "sensors.h"
#include <iostream>

static gpio_num_t i2c_gpio_sda = GPIO_NUM_21;
static gpio_num_t i2c_gpio_scl = GPIO_NUM_22;
static uint32_t i2c_frequency = 100000;
static i2c_port_t i2c_port = I2C_NUM_0;

static uint8_t sensor_address = 0x40;

sensor::sensor()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = i2c_gpio_sda;
    conf.scl_io_num = i2c_gpio_scl;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = i2c_frequency;

    i2c_param_config(i2c_port, &conf);

    i2c_driver_install(i2c_port, I2C_MODE_MASTER, 0, 0, 0 );

    std::cout << "i2c config finished" << std::endl;
}

uint8_t sensor::readFirmware()
{
    const uint8_t cmd_read_firmware[] = {0x84, 0xB8};
    uint8_t firmwareVersion;
    uint8_t *ptr = &firmwareVersion;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (sensor_address << 1 | I2C_MASTER_WRITE), I2C_MASTER_ACK);
    i2c_master_write(cmd, (uint8_t *)cmd_read_firmware, 2, I2C_MASTER_ACK);
    i2c_master_write_byte(cmd, (sensor_address << 1 | I2C_MASTER_READ), I2C_MASTER_ACK);
    i2c_master_read_byte(cmd, ptr, I2C_MASTER_LAST_NACK);
    //i2c_master_read(cmd, )
    
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(i2c_port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return firmwareVersion;
}