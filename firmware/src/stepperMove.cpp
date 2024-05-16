#include "Config.h"
#include "hanleTemplate.tpp"

AccelStepper stepper(AccelStepper::DRIVER, 35, 36); // Ensure these are valid pins

void initializeStepper() {
    stepper.setMaxSpeed(100000.0);
    stepper.setAcceleration(2000.0);
}

// Function to handle moving the stepper to a specific position
void handleMoveStepper(AsyncWebServerRequest *request) {
    handleTemplate<int>(request, "position", [](int pos) { stepper.moveTo(pos); stepper.runToPosition(); }, "Stepper moved to position");
}

// Function to handle setting the acceleration of the stepper
void handleSetAcceleration(AsyncWebServerRequest *request) {
    handleTemplate<float>(request, "value", [](float acc) { stepper.setAcceleration(acc); }, "Acceleration set to");
}

// Function to handle setting the speed of the stepper
void handleSetSpeed(AsyncWebServerRequest *request) {
    handleTemplate<float>(request, "value", [](float speed) { stepper.setMaxSpeed(speed); }, "Speed set to");
}