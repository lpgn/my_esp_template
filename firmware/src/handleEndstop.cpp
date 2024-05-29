
#include "handleEndstop.h"

// constructor for the endstop class
// this is a setup for the endstop class

EndStop::EndStop(int pin)
{
    _pin = pin;
}

// function to initialize the endstop
// this is a setup for the endstop class

void EndStop::init()
{
    pinMode(_pin, INPUT_PULLUP);
}

// function to check if the endstop is triggered

bool EndStop::isEndStopTriggered()
{
    return digitalRead(_pin) == LOW;
}

// function to handle the endstop

void handleEndStop()
{
    static EndStop endStop(endStopPin);
    endStop.init();

    if (endStop.isEndStopTriggered())
    {
        Serial.println("Endstop triggered");
    
    }
}
// Path: src/handleEndstop.cpp
