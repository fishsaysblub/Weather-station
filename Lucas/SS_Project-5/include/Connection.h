#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"

#define SERVER_IP "192.168.1.5"


void StartTask();
void ConnectToWifi(void * pvParameters);
void ConnectToServer();