#ifndef STEPPER_MOVE_H
#define STEPPER_MOVE_H

#include "Config.h"

// Function declarations
void moveStepper();
void stepperToggle();
void handleMoveStepper(AsyncWebServerRequest *request);
void handleSetAcceleration(AsyncWebServerRequest *request);
void handleSetStepsPerMM(AsyncWebServerRequest *request);
void handleToggleStepper(AsyncWebServerRequest *request);


#endif