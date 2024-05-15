#include "Config.h"
#include "stepperMove.h"

AccelStepper stepper(AccelStepper::DRIVER, 25, 26); // Ensure these are valid pins

void initializeStepper() {
    stepper.setMaxSpeed(100000.0);
    stepper.setAcceleration(2000.0);
}

// Function to handle moving the stepper to a specific position
void handleMoveStepper(AsyncWebServerRequest *request) {
    handleSetStepperParameter<int>(request, "position", [](int pos) { stepper.moveTo(pos); stepper.runToPosition(); }, "Stepper moved to position");
}

// Function to handle setting the acceleration of the stepper
void handleSetAcceleration(AsyncWebServerRequest *request) {
    handleSetStepperParameter<float>(request, "value", [](float acc) { stepper.setAcceleration(acc); }, "Acceleration set to");
}

// Function to handle setting the speed of the stepper
void handleSetSpeed(AsyncWebServerRequest *request) {
    handleSetStepperParameter<float>(request, "value", [](float speed) { stepper.setMaxSpeed(speed); }, "Speed set to");
}