#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include <ESP32Servo.h>

extern Servo servo;

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

#endif