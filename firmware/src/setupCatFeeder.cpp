#include "setupCatFeeder.h"

// Function to setup the cat feeder system
void setupFeeder() {
    // Initialize I2C communication
    // Wire.begin(0x04);
    // Wire.onReceive(receiveEvent); // Register an event handler for I2C receive events
    //calibrateReservoir();
}

// Function to calibrate the reservoir
void calibrateReservoir() {
    Serial.println("Calibrating reservoir...");
    // Move the reservoir anti-clockwise until it hits the endstop
    while (digitalRead(endstopPin) != LOW) {
        // Move the reservoir anti-clockwise using the AccelStepper library
        stepperReservoir.move(-1);
        stepperReservoir.runSpeedToPosition();
    }
    // Set the position of the reservoir to 0
    stepperReservoir.setCurrentPosition(0);
}

// the function should receive the module in which the food is fed
void moveReservoir(int modulePosition) {
    // Logic to move the reservoir to the correct module position
    Serial.print("Moving reservoir to position ");
    Serial.println(modulePosition);
    stepperReservoir.moveTo(modulePosition);
    stepperReservoir.runToPosition();
}

void moveScrew(int amount) {
    // Logic to move the screw and dispense food
    Serial.print("Dispensing ");
    Serial.print(amount);
    Serial.println(" grams of food...");
    stepperScrew.moveTo(amount); stepperScrew.runToPosition();
}
