#include "WifiClient.h"

const char* ssid = "POCOX6Pro";    
const char* password = "esppucrs";

IPAddress ip(192, 168, 60, 100);
IPAddress gateway(192, 168, 60, 1);
IPAddress subnet(255, 255, 255, 0);

void WIFIConnect(WiFiClient *espClient)
{
    if (!WiFi.config(ip, gateway, subnet)) {
        Serial.println("Falha ao configurar o IP estático");
    }
    
    Serial.println("Conectando......");
    WiFi.begin(ssid, password);


    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }    
}