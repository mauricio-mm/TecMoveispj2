#include "WebServerClient.h"

void WEBServerConnect(AsyncWebServer& server)
{
    if(!SPIFFS.begin())
    {
        Serial.println("Um errro aconteceu durante a montagem da Flash");
        return;
    }
}

void routes(AsyncWebServer *server) 
{    
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {   
        // if (request->hasParam("value")) {
        //     *option = request->getParam("value")->value().toInt();
        // }

        request->send(SPIFFS, "/index.html", String());
    });

    server->on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        request->send(SPIFFS, "/styles.css", "text/css");
    });
    
    server->on("/bootstrap.css", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        request->send(SPIFFS, "/bootstrap.css", "text/css");
    });    
       
    server->on("/images.jpg", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        request->send(SPIFFS, "/images.jpg", "image/jpeg");
    });

    server->begin();
}