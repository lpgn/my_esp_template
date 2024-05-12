#include "Config.h"
#include "stepperMove.h"

AccelStepper stepper(AccelStepper::DRIVER, 25, 26);
bool toggleStepper = false; // Global flag for toggling stepper direction
bool toggleDirection = false;  // This will keep track of the direction internally

void moveStepper() {
    stepper.setMaxSpeed(100000.0);
    stepper.setAcceleration(2000.0);
    stepper.moveTo(0);
    stepper.runToPosition();
}

void stepperToggle() {
    if (toggleDirection) {
        long currentPosition = stepper.currentPosition();
        // Toggle the target position to the opposite side of the current position
        if (currentPosition == 0) {
            stepper.moveTo(1000);  // Example position, adjust based on your use case
        } else {
            stepper.moveTo(-currentPosition);
        }
        toggleDirection = false;  // Reset the toggle flag
        Serial.print("Current Position: "); Serial.println(currentPosition);
        Serial.print("Moving to Position: "); Serial.println(currentPosition > 0 ? -currentPosition : 1000);
    }
    stepper.run();  // Regularly call this to update stepper position and handle direction changes

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
        stepper.runToPosition(); // This blocks until the position is reached, consider using stepper.run() in loop for non-blocking behavior
        request->send(200, "text/plain", "Stepper moved to position: " + String(position));
    } else {
        request->send(400, "text/plain", "Position parameter is missing");
    }
}

// Function to handle setting the acceleration of the stepper
void handleSetAcceleration(AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
        float acceleration = request->getParam("value")->value().toFloat();
        stepper.setAcceleration(acceleration);
        request->send(200, "text/plain", "Acceleration set to: " + String(acceleration));
    } else {
        request->send(400, "text/plain", "Acceleration parameter is missing");
    }
}


// Function to handle setting the acceleration of the stepper
void handleSetSpeed(AsyncWebServerRequest *request) {
    if (request->hasParam("value")) {
        float speed = request->getParam("value")->value().toFloat();
        stepper.setMaxSpeed(speed);
        request->send(200, "text/plain", "Speed set to: " + String(speed));
    } else {
        request->send(400, "text/plain", "Speed parameter is missing");
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