#include "setupCatFeeder.h"

// Function to setup the cat feeder system
void setupFeeder() {
    // Initialize I2C communication
    // Wire.begin(0x04);
    // Wire.onReceive(receiveEvent); // Register an event handler for I2C receive events
    calibrateReservoir();
    printAsciiBox("Feeder setup complete");
}



void calibrateReservoir() {
    Serial.println("Calibrating reservoir...");
    while (digitalRead(endStopPin) != LOW) {
        stepperReservoir.move(-1);
        stepperReservoir.runSpeedToPosition();
        // Check for endstop hit
        endstopDebouncer.update();
        if (endstopDebouncer.fell()) {
            printAsciiBox("Endstop clicked!");
            break; // Exit the loop as endstop is hit
        }
    }
    stepperReservoir.setCurrentPosition(0);
    printAsciiBox("Reservoir calibrated");
}
