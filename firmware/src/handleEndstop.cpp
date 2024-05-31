#include "handleEndstop.h"

Bounce endstopDebouncer = Bounce();
volatile bool endstopHit = false;
volatile bool endstopReleased = false;

void setupEndstopInterrupt(int pin) {
    pinMode(pin, INPUT_PULLUP);
    endstopDebouncer.attach(pin);
    endstopDebouncer.interval(50); // Set debounce interval to 50ms
}

void updateEndstopState() {
    endstopDebouncer.update();
    if (endstopDebouncer.fell()) {
        endstopHit = true;
    } else if (endstopDebouncer.rose()) {
        endstopReleased = true;
    }
}

bool checkEndstopHit() {
    if (endstopHit) {
        endstopHit = false;
        return true;
    }
    return false;
}

bool checkEndstopReleased() {
    if (endstopReleased) {
        endstopReleased = false;
        return true;
    }
    return false;
}