#include <Arduino.h>
#include <stdio.h>

#include "Connection.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Setup starting");
  StartTask();
}

void loop() {
  // put your main code here, to run repeatedly:
}