#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#include "main.h"
#include "FS.h"
#include "SPIFFS.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define LEDPIN 4

#define DHTPIN 16
#define DHTTYPE DHT22

#define RELEPIN 17

#define SERVOPIN 5

void UtilsConfig(DHT *dht);

String le_umid(DHT *dht);
String le_temp(DHT *dht);
#endif