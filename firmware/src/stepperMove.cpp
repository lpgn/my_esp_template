#include "Config.h"

AccelStepper stepper(AccelStepper::DRIVER, 25, 26);

void initializeStepper() {
    stepper.setMaxSpeed(100000.0);
    stepper.setAcceleration(2000.0);
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