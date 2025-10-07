#pragma once

#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

#include "main.h"
#include "FS.h"
#include "SPIFFS.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>

#define LEDPIN 2

#define DHTPIN 4
#define DHTTYPE DHT22

#define RELEPIN 3

#define SERVOPIN 16

void UtilsConfig(DHT *dht);

String le_umid(DHT *dht);
String le_temp(DHT *dht);
#endif