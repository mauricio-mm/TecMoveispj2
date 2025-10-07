
#include "utils.h"

void UtilsConfig(DHT *dht)
{  
    //LED PIN 
    pinMode(LEDPIN, OUTPUT);
    digitalWrite(LEDPIN, HIGH);

    //DHT CONF
    dht->begin();
    pinMode(DHTPIN, INPUT);

    //RELE CONF
    pinMode(RELEPIN, OUTPUT);
    
    //SERVO CONF
    servo.attach(SERVOPIN);
}

String le_temp(DHT *dht)
{
 return String(dht->readTemperature(), 2);
}

String le_umid(DHT *dht)
{
 return String(dht->readHumidity(), 2);
}