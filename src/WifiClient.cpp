#include "WifiClient.h"

bool config_ap = false;
bool config_spa = false;

const char* ssid_STA = "POCOX6Pro";    
const char* password_STA = "esppucrs";

const char* ssid_AP = "ESP32_Server";
const char* password_AP = "12345678";

bool config_AP();
bool config_SPA();

void WIFIConnect()
{
    Serial.println("Inicializando Wi-Fi em modo dual (STA + AP)...");
    WiFi.mode(WIFI_AP_STA);

    if (!config_ap) config_ap = config_AP();
    if (!config_spa) config_spa = config_SPA();
}

bool config_AP()
{
    File file = SPIFFS.open("/config.txt", "r");
    if(!file){
        Serial.println("Erro ao abrir config.txt");
        return false;
    }

    String ipStr = file.readString();
    file.close();
    ipStr.trim();

    IPAddress localIP, gateway(192,168,1,1), subnet(255,255,255,0);
    if(!localIP.fromString(ipStr)){
        Serial.println("IP invalido no config.txt");
        return false;
    }

    if(!WiFi.softAPConfig(localIP, gateway, subnet)){
        Serial.println("Falha ao configurar IP estático do AP");
        return false;
    }

    bool apStarted = WiFi.softAP(ssid_AP, password_AP);
    if(apStarted){
        Serial.println("Access Point iniciado com sucesso!");
        Serial.print("  SSID: "); Serial.println(ssid_AP);
        Serial.print("  IP local: "); Serial.println(WiFi.softAPIP());
        return true;
    }
    else{
        Serial.println("Falha ao iniciar Access Point!");
        return false;
    }
}

bool config_SPA()
{
    Serial.print("Conectando a rede Wi-Fi ");
    Serial.println(ssid_STA);
    WiFi.begin(ssid_STA, password_STA);

    int tentativas = 0;
    while (WiFi.status() != WL_CONNECTED && tentativas < 15)
    {
        delay(1000);
        Serial.print(".");
        tentativas++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("\nConectado ao Wi-Fi!");
        Serial.print("IP local STA: ");
        Serial.println(WiFi.localIP());
        return true;
    }
    else Serial.println("\nFalha ao conectar a rede Wi-Fi STA.");

    return false;
}