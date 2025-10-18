#include <Arduino.h>
#include <Adafruit_Sensor.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "main.h"
#include "WifiClient.h"
#include "MQTTClient.h"
#include "WebServerClient.h"
#include "utils.h"

AsyncWebServer server(80);
WiFiClient     espClient;
PubSubClient   MQTT(espClient);

DHT            dht(DHTPIN, DHTTYPE);
Servo          servo;

static long long pooling = 0;

void listSPIFFS() {
    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
        Serial.print("Arquivo encontrado: ");
        Serial.println(file.name());
        file = root.openNextFile();
    }
}

void setup() 
{  
    Serial.begin(9600);
    
       if(!SPIFFS.begin(true)) {
        Serial.println("Erro ao montar SPIFFS");
        return;
    }

    listSPIFFS(); 

    WIFIConnect();
    WEBServerConnect(&server);
    MQTTConnect(&MQTT);    
    UtilsConfig(&dht);
} 

void loop() 
{
  
  if(WiFi.status() == WL_CONNECTED)
  { 
    if(!MQTT.connected()) MQTTConfig(&MQTT);

    if(pooling > 100000)
    {

      Serial.println("DHT: " + String(dht.readTemperature()) + ':' + String(dht.readHumidity()));

      if (!isnan(dht.readTemperature()) && !isnan(dht.readHumidity()))
      {
        publish_data(&MQTT, topic_dht, String(dht.readTemperature()) + ':' +String(dht.readHumidity()));
      }

      pooling = 0;
    }else pooling++;

    MQTT.loop(); 
  }else WIFIConnect();  


}