#include "setupCatFeeder.h"

// Function to setup the cat feeder system
void setupFeeder() {
    // Initialize I2C communication
    // Wire.begin(0x04);
    // Wire.onReceive(receiveEvent); // Register an event handler for I2C receive events
    //calibrateReservoir();
    calibrateReservoir();
    printAsciiBox("Feeder setup complete");
}

// Function to calibrate the reservoir
void calibrateReservoir() {
    Serial.println("Calibrating reservoir...");
    // Move the reservoir anti-clockwise until it hits the endstop
    while (digitalRead(endStopPin) != LOW) {
        // Move the reservoir anti-clockwise using the AccelStepper library
        stepperReservoir.move(-1);
        stepperReservoir.runSpeedToPosition();
    }
    // Set the position of the reservoir to 0
    stepperReservoir.setCurrentPosition(0);
    printAsciiBox("Reservoir calibrated");
}

void checkEndstop() {
    if (digitalRead(endStopPin) == LOW) {
        printAsciiBox("Endstop clicked");
    }
}
