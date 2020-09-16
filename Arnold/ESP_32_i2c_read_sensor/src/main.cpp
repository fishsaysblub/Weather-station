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
        //printf("Hello from thread 1\n");
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
        //printf("Hello from thread 2\n");
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
        //printf("Hello from thread 3\n");
        gpio_set_level(REDLED, 1);
        vTaskDelay(400 / portTICK_RATE_MS);

        gpio_set_level(REDLED, 0);
        vTaskDelay(400 / portTICK_RATE_MS);
    }
}

void app_main()
{
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = (1ULL << ORANGELED)  | (1ULL << GREENLED) | (1ULL << REDLED);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;

    gpio_config(&io_conf);

        // Set WiFi to station mode and disconnect from an AP if it was previously connected
  //  WiFi.mode(WIFI_STA);
  //  WiFi.disconnect();


    sensor temp;
    temp.test = 3;

    printf("Firmware version = %d\n", temp.readFirmware());
    // std::cout << "firmware version: " << std::hex << std::uppercase << temp.readFirmware() << std::endl;

    std::cout << "App_main()" << std::endl;

    printf("Hello world!\n");

    xTaskCreate(gpio_task1, "gpio_task1", 2048, NULL, 10, NULL);
    xTaskCreate(gpio_task2, "gpio_task2", 2048, NULL, 11, NULL);
    xTaskCreate(gpio_task3, "gpio_task3", 2048, NULL, 12, NULL);
}





/*


void setup()
{
    Serial.begin(115200);


    delay(100);

    Serial.println("Setup done");
}

void loop()
{
    Serial.println("scan start");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("scan done");
    if (n == 0) {
        Serial.println("no networks found");
    } else {
        Serial.print(n);
        Serial.println(" networks found");
        for (int i = 0; i < n; ++i) {
            // Print SSID and RSSI for each network found
            Serial.print(i + 1);
            Serial.print(": ");
            Serial.print(WiFi.SSID(i));
            Serial.print(" (");
            Serial.print(WiFi.RSSI(i));
            Serial.print(")");
            Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN)?" ":"*");
            delay(10);
        }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
}
*/