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
          MQTT->subscribe(topic_rele);
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
  if(String(topic) == topic_led) 
  {       
    String msg = "";

    for (unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }

    int sepIndex = msg.indexOf(':');
    if (sepIndex > 0) {
        String on_off = msg.substring(0, sepIndex);
        int dimmer = msg.substring(sepIndex + 1).toInt();
        
        Serial.println("Led: " + msg);

        if (on_off == "True" && dimmer > 0) {
          analogWrite(LEDPIN, map(dimmer, 0, 4, 0, 255));
        } else {
          digitalWrite(LEDPIN, LOW);
        }
    } else {
        Serial.println("Formato inválido de payload!");
    }

  }

  if (String(topic) == topic_rele) 
  { 
      String msg = "";

      for (unsigned int i = 0; i < length; i++) {
          msg += (char)payload[i];
      }    

      msg.trim();
      Serial.println("Rele: " + msg);

      bool on_off = (msg == "True") ? true : false;
      digitalWrite(LEDPIN, on_off ? HIGH : LOW);

  }

  if(String(topic) == topic_servo) 
  {    
    String msg = "";

      for (unsigned int i = 0; i < length; i++) {
          msg += (char)payload[i];
      }    

      msg.trim();
      Serial.println("Servo: " + msg);
      //servo.write(atoi(msg));      
  }
  
}