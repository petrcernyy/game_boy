#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

typedef struct{
    
    int SwitchUpstate;
    int SwitchUpConn;
    int SwitchDownState;
    int SwitchDownConn;
    int SwitchRightState;
    int SwitchRightConn;
    int SwitchLeftState;
    int SwitchLeftConn;

    int contup;
    int contdown;
    int contright;
    int contleft;
}buttonsdebounc;

#endif