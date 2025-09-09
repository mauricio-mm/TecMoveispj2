#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>

#define ID_MQTT "esp_iot"
#define topic_led   "lab318/led"
#define topic_dht   "lab318/dht"
#define topic_servo "lab318/servo"
#define topic_rele  "lab318/servo"

void MQTTConnect (PubSubClient *MQTT);
void MQTTConfig  (PubSubClient *MQTT);
void publish_data(PubSubClient *MQTT, const char *topic, String data);
void callback    (char *topic, byte *payload, unsigned int length);

#endif