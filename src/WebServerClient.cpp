#include "WebServerClient.h"

struct Auth {
    String login;
    String password;
    bool auth;

    Auth() {
        login = "admin";
        password = "123456";
        auth = false;
    }
};

Auth user;

void WEBServerConnect(AsyncWebServer *server)
{
    if(!SPIFFS.begin())
    {
        Serial.println("Um errro aconteceu durante a montagem da Flash");
        return;
    }else Serial.println("Server On");

    routes(server);
}

void routes(AsyncWebServer *server) 
{    
    server->on("/", HTTP_GET, [](AsyncWebServerRequest *request)
    {  
        request->send(SPIFFS, "/index.html", "text/html");
    });

    server->on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        request->send(SPIFFS, "/styles.css", "text/css");
    });
    
    server->on("/bootstrap.css", HTTP_GET, [](AsyncWebServerRequest *request) 
    {
        request->send(SPIFFS, "/bootstrap.css", "text/css");
    });    

    server->on("/login", HTTP_POST, [](AsyncWebServerRequest *request) 
    {
        String receivedLogin = "";
        String receivedPassword = "";
        String status = "failure";
        
        Serial.println(request->args());
        if (request->hasArg("login") && request->hasArg("password")) 
        {
            receivedLogin = request->arg("login");
            receivedPassword = request->arg("password");

            if (receivedLogin == user.login && receivedPassword == user.password) {
                user.auth = true;
                status = "success";
            } else {
                user.auth = false;
                status = "failure"; 
            }
        } 

        File file = SPIFFS.open("/index.html", "r");
        if(!file){
            request->send(500, "text/plain", "Erro ao abrir index.html");
            return;
        }

        String html = file.readString();
        file.close();

        if (user.auth) 
        {
            request->send(SPIFFS, "/login.html", "text/html");
            return;
        }else {
            html.replace("{{status}}", status);
            request->send(200, "text/html", html);
            request->redirect("/");
            return;
        }
    });

    server->on("/set_config", HTTP_POST, [](AsyncWebServerRequest *request) 
    {   
        Serial.println('Request: ');
        if (request->hasArg("newIP")) 
        {      
            Serial.println(request->arg("newIP"));
            String newIP = request->arg("newIP");
            newIP.trim();
            String oldContent = "";
            if (SPIFFS.exists("/config.txt")) {
                File oldFile = SPIFFS.open("/config.txt", "r");
                if (oldFile) {
                    oldContent = oldFile.readString();
                    oldFile.close();
                }
            }

            Serial.println("----- [ANTES DA MODIFICAÇÃO] -----");
            Serial.println(oldContent);
            Serial.println("----------------------------------");
            File file = SPIFFS.open("/config.txt", "w");
            if(!file){
                request->send(500, "text/plain", "Erro ao abrir config.txt");
                return;
            } 

            file.print(newIP);
            file.flush();
            file.seek(0);
            String newContent = file.readString();

            Serial.println("----- [DEPOIS DA MODIFICAÇÃO] -----");
            Serial.println(newContent);
            Serial.println("-----------------------------------");

            file.close();

            request->send(200, "text/plain", "Arquivo sobrescrito com sucesso!");
            return;
        }

        request->send(400, "text/plain", "Arquivo sobrescrito falhou");
    });


    server->begin();
}