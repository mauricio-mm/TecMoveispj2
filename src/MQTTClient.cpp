#include "MQTTClient.h"

const char* mqtt_broker = "broker.emqx.io";
const int mqtt_port = 1883;

void MQTTConnect(PubSubClient *MQTT)
{
    MQTT->setServer(mqtt_broker, mqtt_port);   
    MQTT->setCallback(callback);
}

void MQTTConfig(PubSubClient *MQTT) 
{
    while(!MQTT->connected()) 
    {
        if (MQTT->connect(ID_MQTT))
        {
        Serial.println("Conectado ao Broker!");
        MQTT->subscribe(topic_led);
        MQTT->subscribe(topic_servo);      
        } 
        else 
        {
        Serial.print("Falha na conexão. O status é: ");
        Serial.print(MQTT->state());      
        }
    }
}

void publish_data(PubSubClient *MQTT,const char *topic, String data)
{
  MQTT->publish(topic, data.c_str());
}

void callback(char *topic, byte *payload, unsigned int length) 
{
  if(String(topic) == "lab318/led") 
  {          
  }

  if(String(topic) == "lab318/servo") 
  {    

  }
  
}