#ifndef WEBSERVERCLIENT_H
#define WEBSERVERCLIENT_H

#include <Arduino.h>
#include <ESPAsyncWebServer.h>

#include "main.h"
#include "FS.h"
#include "SPIFFS.h"
#include "utils.h"

void WEBServerConnect(AsyncWebServer *server, Auth *user);
void routes(AsyncWebServer *server, Auth *user);

#endif