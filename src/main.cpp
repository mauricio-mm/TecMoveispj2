#include <Arduino.h>
#include <Adafruit_Sensor.h>

#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <PubSubClient.h>
#include <DHT.h>

#include "WifiClient.h"
#include "MQTTClient.h"
#include "WebServerClient.h"
#include "utils.h"

AsyncWebServer server(80);
WiFiClient     espClient;
PubSubClient   MQTT(espClient);

DHT            dht(DHTPIN, DHTTYPE);
Servo          servo;

static long long tempo=0;

void setup() 
{  
    Serial.begin(9600);
    
    WIFIConnect(&espClient);
    WEBServerConnect(&server);
    MQTTConnect(&MQTT);    
    UtilsConfig(&dht, &servo);
} 

void loop() 
{
  static long long pooling = 0;
  
  if(!MQTT.connected()) MQTTConfig(&MQTT);
  if(WiFi.status() != WL_CONNECTED) WIFIConnect(&espClient);
  
  if(millis()>pooling+5000)
  {
    pooling = millis();
    publish_data(&MQTT, topic_dht, String(dht.readTemperature()) + ':' +String(dht.readHumidity()));
  }  

  MQTT.loop();
}