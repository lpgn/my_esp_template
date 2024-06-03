#include "Config.h"
#include "hanleTemplate.tpp"

// declare stepper driver pins
#define STEPPER1_STEP_PIN 40
#define STEPPER1_DIR_PIN 13
#define STEPPER1_ENA_PIN 7


// Define the stepper motor fi
AccelStepper stepper(AccelStepper::DRIVER, STEPPER1_STEP_PIN, STEPPER1_DIR_PIN, STEPPER1_ENA_PIN);

void initializeStepper() {
    stepper.setMaxSpeed(100.0);
    stepper.setAcceleration(100.0);
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