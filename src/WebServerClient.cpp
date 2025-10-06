#include "WebServerClient.h"

void WEBServerConnect(AsyncWebServer *server, Auth *user)
{
    if(!SPIFFS.begin())
    {
        Serial.println("Um errro aconteceu durante a montagem da Flash");
        return;
    }

    routes(server, user);
}

void routes(AsyncWebServer *server, Auth *user) 
{    
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {   
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

    server->on("/login", HTTP_POST, [&user](AsyncWebServerRequest *request) 
    {
        String receivedSSID = "";
        String receivedPassword = "";
        
        if (request->hasParam("ssid", true) && request->hasParam("password", true)) 
        {
            receivedSSID = request->getParam("ssid", true)->value();
            receivedPassword = request->getParam("password", true)->value();
            
            if (receivedSSID == user->login && receivedPassword == user->password) {
                user->auth = true;
                request->redirect("/index.html?status=success");
            } else {
                user->auth = false;
                request->redirect("/index.html?status=failure");
            }
        } 
        else 
        {
            request->redirect("/index.html?status=failure");
        }
    });

    server->begin();
}