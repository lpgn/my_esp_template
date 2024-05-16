#ifndef STEPPER_MOVE_H
#define STEPPER_MOVE_H

#include "Config.h"

// Function declarations
void initializeStepper();
void handleMoveStepper(AsyncWebServerRequest *request);
void handleSetAcceleration(AsyncWebServerRequest *request);
void handleSetSpeed(AsyncWebServerRequest *request);

// Template function declaration
template <typename T>
void handleTemplate(AsyncWebServerRequest *request, const char* paramName, void (*setterFunction)(T), const char* successMessage);

#endif
