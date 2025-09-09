#ifndef WEBSERVERCLIENT_H
#define WEBSERVERCLIENT_H

#include <Arduino.h>
#include <WebServer.h>
#include <ESPAsyncWebServer.h>

#include "FS.h"
#include "SPIFFS.h"
#include "utils.h"

void WEBServerConnect(AsyncWebServer *server);
void routes(AsyncWebServer& server) ;

#endif