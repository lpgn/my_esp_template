// header file for handleEndstop.c
#ifndef HANDLEENDSTOP_H
#define HANDLEENDSTOP_H

#include <Arduino.h>

extern const int endStopPin;

class EndStop
{
public:
    EndStop(int pin);
    void init();
    bool isEndStopTriggered();

private:
    int _pin;
};

#endif