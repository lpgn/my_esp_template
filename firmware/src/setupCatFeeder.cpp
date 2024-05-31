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



void calibrateReservoir() {
    Serial.println("Calibrating reservoir...");
    while (digitalRead(endStopPin) != LOW && !checkEndstopHit()) {
        stepperReservoir.move(-1);
        stepperReservoir.runSpeedToPosition();
    }
    stepperReservoir.setCurrentPosition(0);
    printAsciiBox("Reservoir calibrated");
}

