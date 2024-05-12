#include "Config.h"
#include "stepperMove.h"

AccelStepper stepper(AccelStepper::DRIVER, 25, 26);
bool toggleStepper = false; // Global flag for toggling stepper direction
bool toggleDirection = false;  // This will keep track of the direction internally

void moveStepper() {
    stepper.setMaxSpeed(1000.0);
    stepper.setAcceleration(200.0);
    stepper.moveTo(60000);
    stepper.runToPosition();
}

void stepperToggle() {
    if (toggleDirection) {
        long currentPosition = stepper.currentPosition();  // Get the current position
        stepper.moveTo(-currentPosition);  // Set the target position to the negative of the current position to reverse direction
        toggleDirection = false;  // Reset the toggle flag
    }
    stepper.run();  // This needs to be called regularly to make the motor move
}

void handleToggleStepper(AsyncWebServerRequest *request) {
    toggleDirection = true;  // This will toggle the motor direction on the next check in stepperToggle()
    request->send(200, "text/plain", "Stepper direction will be toggled");
}

// Function to handle moving the stepper to a specific position
void handleMoveStepper(AsyncWebServerRequest *request) {
    if (request->hasParam("position")) {
        int position = request->getParam("position")->value().toInt();
        stepper.moveTo(position);
        stepper.runToPosition();
        Serial.println("Received moveStepper command: Moving to position " + String(position));
        request->send(200, "text/plain", "Stepper moved to position: " + String(position));
    } else {
        request->send(400, "text/plain", "Position parameter is missing");
    }
}

// Function to handle setting the acceleration of the stepper
void handleSetAcceleration(AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
        int acceleration = request->getParam("value")->value().toInt();
        stepper.setAcceleration(acceleration);
        Serial.println("Received setAcceleration command: Setting acceleration to " + String(acceleration));
        request->send(200, "text/plain", "Acceleration set to: " + String(acceleration));
    } else {
        request->send(400, "text/plain", "Acceleration parameter is missing");
    }
}

// Function to handle setting the steps per mm
void handleSetStepsPerMM(AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
        int stepsPerMM = request->getParam("value")->value().toInt();
        // Assuming functionality to set steps per mm if applicable
        Serial.println("Received setStepsPerMM command: Setting steps per mm to " + String(stepsPerMM));
        request->send(200, "text/plain", "Steps per mm set to: " + String(stepsPerMM));
    } else {
        request->send(400, "text/plain", "Steps per mm parameter is missing");
    }
}