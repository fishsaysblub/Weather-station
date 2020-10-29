#include <I2C.h>
#include <string.h>

I2C::I2C()
{
    i2c_config_t config;
    InitI2CConfig(&config);
    Initialise(&config);
}

void I2C::InitI2CConfig(i2c_config_t * config)
{
    memset(config, 0, sizeof(*config));       
    config->mode = I2C_MODE_MASTER;
    config->sda_io_num = GPIO_NUM_21;
    config->scl_io_num = GPIO_NUM_22;
    config->sda_pullup_en = GPIO_PULLUP_ENABLE;
    config->scl_pullup_en = GPIO_PULLUP_ENABLE;
    config->master.clk_speed = FAST_I2C;
}

void I2C::Initialise(i2c_config_t * config)
{
    i2c_param_config(I2C_NUM_0, config);

    i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER, 0, 0, 0);

    printf("i2c config finished\n");
}

void I2C::WriteCmd(CMDData * cmd_data)
{
     if(cmd_data->Len <=0 || !(*cmd_data->Buffer))
        return;

    i2c_cmd_handle_t cmd;
    Start(&cmd, cmd_data->Address, I2C_MASTER_WRITE);

    for (int i = 0; i < cmd_data->Len; i++)
        i2c_master_write_byte(cmd, cmd_data->Buffer[i], I2C_MASTER_ACK);

    Reset(&cmd);
}

void I2C::ReadCmd(CMDData * cmd_data)
{
     if(cmd_data->Len <=0 || !(*cmd_data->Buffer))
        return;
    
    i2c_cmd_handle_t cmd;
    Start(&cmd, cmd_data->Address, I2C_MASTER_READ);

    for (int i = 0; i < cmd_data->OutputLen; i++)
        i2c_master_read_byte(cmd, &cmd_data->OutputBuffer[i], 
                            i == cmd_data->OutputLen - 1 ? I2C_MASTER_NACK : I2C_MASTER_ACK);

    Reset(&cmd);
}

void I2C::Start(i2c_cmd_handle_t * cmd_handle, uint8_t address, i2c_rw_t rw)
{
    *(cmd_handle) = i2c_cmd_link_create();
    i2c_master_start(*(cmd_handle));
    i2c_master_write_byte(*(cmd_handle), (address << 1 | rw), I2C_MASTER_ACK); // Write the address to the slave to read.
}

void I2C::Reset(i2c_cmd_handle_t * cmd)
{
    ESP_ERROR_CHECK(i2c_master_stop(*cmd));
    ESP_ERROR_CHECK(i2c_master_cmd_begin(I2C_NUM_0, *cmd, 1000 / portTICK_RATE_MS));
    i2c_cmd_link_delete(*cmd);
}