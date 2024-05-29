// header file for handleEndstop.c
#ifndef HANDLEENDSTOP_H
#define HANDLEENDSTOP_H

#include <config.h>

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