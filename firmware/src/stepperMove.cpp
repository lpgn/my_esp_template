#include "Config.h"
#include "hanleTemplate.tpp"

// declare stepper driver pins
#define STEPPER1_STEP_PIN 38
#define STEPPER1_DIR_PIN 37

// Define the stepper motor fi
AccelStepper stepper(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN);

void initializeStepper() {
    stepper.setMaxSpeed(100000.0);
    stepper.setAcceleration(2000.0);
}

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