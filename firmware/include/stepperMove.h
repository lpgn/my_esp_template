#ifndef STEPPER_MOVE_H
#define STEPPER_MOVE_H

#include "Config.h"

// Function declarations
void initializeStepper();
void handleMoveStepper(AsyncWebServerRequest *request);
void handleSetAcceleration(AsyncWebServerRequest *request);
void handleSetSpeed(AsyncWebServerRequest *request);

#endif