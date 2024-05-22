#include "Config.h"
#include "templates.tpp"

// Function to handle moving the stepper to a specific position
void handleMoveStepper(AsyncWebServerRequest *request) {
    handleTemplate<int>(request, "position", [](int pos) { stepperReservoir.moveTo(pos); stepperReservoir.runToPosition(); }, "Stepper moved to position");
}

// Function to handle setting the acceleration of the stepper
void handleSetAcceleration(AsyncWebServerRequest *request) {
    handleTemplate<float>(request, "value", [](float acc) { stepperReservoir.setAcceleration(acc); }, "Acceleration set to");
}

// Function to handle setting the speed of the stepper
void handleSetSpeed(AsyncWebServerRequest *request) {
    handleTemplate<float>(request, "value", [](float speed) { stepperReservoir.setMaxSpeed(speed); }, "Speed set to");
}