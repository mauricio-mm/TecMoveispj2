#include "WifiClient.h"

const char* ssid = "POCOX6Pro";    
const char* password = "esppucrs";

void WIFIConnect(WiFiClient *espClient)
{    
    
    Serial.println("Conectando......");
    WiFi.begin(ssid, password);


    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(1000);
        Serial.print(".");
    }    
}