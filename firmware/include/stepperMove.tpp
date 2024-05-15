#ifndef STEPPER_MOVE_TPP
#define STEPPER_MOVE_TPP

#include "config.h"

// Template function implementation
template <typename T>
void handleSetStepperParameter(AsyncWebServerRequest *request, const char* paramName, void (*setterFunction)(T), const char* successMessage) {
    if (request->hasParam(paramName)) {
        T value = static_cast<T>(request->getParam(paramName)->value().toDouble());
        Serial.printf("Setting stepper %s to: %f\n", paramName, static_cast<float>(value));
        setterFunction(value);
        request->send(200, "text/plain", String(successMessage) + ": " + String(value));
    } else {
        request->send(400, "text/plain", String(paramName) + " parameter is missing");
    }
}

#endif
