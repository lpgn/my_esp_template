//cat feeder code
#include "setupCatFeeder.h"
// Function to setup the cat feeder system
void setupFeeder() {
     // Initialize I2C communication
    Wire.begin(0x04);
    Wire.onReceive(receiveEvent); // Register an event handler for I2C receive events
    calibrateReservoir();
    checkFeedingSchedule();
}
// note to future Bianca: eventually change the homing speed to slower when aproaching 0
// Function to calibrate the reservoir
void calibrateReservoir() {
    Serial.println("Calibrating reservoir...");
    // Move the reservoir anti-clockwise until it hits the endstop
    while (digitalRead(endstopPin) != LOW) {
        // Move the reservoir anti-clockwise using the AceelStepeer library
        stepperReservoir.move(-1);
        stepperReservoir.runSpeedToPosition(); 
    }
    // Set the position of the reservoir to 0
    stepperReservoir.setCurrentPosition(0);
}

void moveReservoir() {
    // Logic to move the reservoir
    Serial.println("Moving reservoir...");
    // Example: stepperReservoir.moveTo(0); stepperReservoir.runToPosition();
}

void moveScrew(int amount) {
    // Logic to move the screw and dispense food
    Serial.print("Dispensing ");
    Serial.print(amount);
    Serial.println(" grams of food...");
    // Example: stepperScrew.moveTo(amount); stepperScrew.runToPosition();
}