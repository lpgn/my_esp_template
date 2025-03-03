#include "handleEndstop.h"

void setupEndstopInterrupt(int pin) {
    pinMode(pin, INPUT_PULLUP);
    endstopDebouncer.attach(pin);
    endstopDebouncer.interval(50); // Set debounce interval to 50ms
}