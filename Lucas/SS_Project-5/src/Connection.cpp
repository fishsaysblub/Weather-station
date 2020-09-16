#include "Connection.h"

TaskHandle_t _handle;
WiFiClient clien;

void StartTask()
{
    xTaskCreatePinnedToCore(
    ConnectToWifi,
    "WifiConnect",
    10000,
    NULL,
    1,
    &_handle,
    0);
}

void ConnectToWifi(void * pvParameters)
{
  Serial.print("Task running on core: ");
  Serial.println(xPortGetCoreID());
  Serial.print("Connecting to wifi");
  WiFi.begin("NETGEAR18", "wittycheese610");
  while(WiFi.status() != WL_CONNECTED)
  { 
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  ConnectToServer();
}

void ConnectToServer()
{
  
 if(!clien.connect(SERVER_IP, 80))
 {
  Serial.println("Failed to connect to server.");
  delay(1000);
  return;
 }

  Serial.println("Connected to server!");
  clien.print("GET /SS_Project-5/data.php?");
  clien.print("reading=");
  clien.print("temp");
  clien.print("&value=");
  clien.println(6.73);
  clien.stop();

  delay(1000);
}
