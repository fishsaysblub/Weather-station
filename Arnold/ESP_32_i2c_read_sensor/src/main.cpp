#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"
#include "esp_wifi.h"

#include "sensors.h"

#include <iostream>

#define ORANGELED  GPIO_NUM_23
#define GREENLED   GPIO_NUM_19
#define REDLED     GPIO_NUM_18

extern "C" {
    void app_main(void);
}


void gpio_task1(void *arg)
{


    while (1)
    {
        std::cout << "Thread 1 here" << std::endl;
        
        gpio_set_level(ORANGELED, 1);
        vTaskDelay(100 / portTICK_RATE_MS);

        gpio_set_level(ORANGELED, 0);
        vTaskDelay(100 / portTICK_RATE_MS);
    }
}

void gpio_task2(void *arg)
{
    while (1)
    {
        std::cout << "Thread 2 here" << std::endl;

        gpio_set_level(GREENLED, 1);
        vTaskDelay(200 / portTICK_RATE_MS);

        gpio_set_level(GREENLED, 0);
        vTaskDelay(200 / portTICK_RATE_MS);
    }
}

void gpio_task3(void *arg)
{
    while (1)
    {
        std::cout << "Thread 3 here" << std::endl;
        
        gpio_set_level(REDLED, 1);
        vTaskDelay(400 / portTICK_RATE_MS);

        gpio_set_level(REDLED, 0);
        vTaskDelay(400 / portTICK_RATE_MS);
    }
}


void readTempTask(void *arg)
{
       sensor temp;
    
    while (1)
    {
       temp.readHumidity(); //readTemperature();
        vTaskDelay(1000 / portTICK_RATE_MS);
    }
}

void app_main()
{
    std::cout << "App_main()" << std::endl;

    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << ORANGELED)  | (1ULL << GREENLED) | (1ULL << REDLED);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;

    gpio_config(&io_conf);

    // xTaskCreate(gpio_task1, "gpio_task1", 2048, NULL, 10, NULL);
    // xTaskCreate(gpio_task2, "gpio_task2", 2048, NULL, 11, NULL);
    //xTaskCreate(gpio_task3, "gpio_task3", 2048, NULL, 12, NULL);
    xTaskCreate(readTempTask, "read_temp", 2048, NULL, 9, NULL);
}