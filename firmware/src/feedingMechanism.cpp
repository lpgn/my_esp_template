//feeding mechanism code

#include "feedingMechanism.h"

void initializeStepper() {
   //note to self: add the correct values for the max speed and acceleration
    stepperReservoir.setMaxSpeed(100000.0); 
    stepperReservoir.setAcceleration(2000.0); 
    stepperScrew.setMaxSpeed(100000.0);
    stepperScrew.setAcceleration(2000.0);
}

// Function to determine the required amount of food
void determineFoodAmount(const String& catName, int foodAmount) {
    // Example calculations - replace with your actual logic
    int stepsMotor2 = foodAmount * 10; // Steps per gram for X amount of food

    Serial.print("Determining food amount for cat: ");
    Serial.print(catName);
    Serial.print(", Food amount: ");
    Serial.print(foodAmount);
    Serial.print(" grams, Steps for Motor 2: ");
    Serial.println(stepsMotor2);
    // code to return the steps for the motor
    return stepsMotor2;
}

// Function to rotate the reservoir to the correct position
void rotateReservoir() {
    // Code to rotate the reservoir
    Serial.println("Rotating reservoir...");
}

// Function to rotate the feed screw to dispense food
void rotateFeedScrew(int stepsMotor2) {
    // Code to rotate the feed screw
    stepperScrew.move(stepsMotor2);
    while (stepperScrew.distanceToGo() != 0) {
        stepperScrew.run();
    }
    Serial.println("Rotating feed screw...");
}

// Function to handle the entire feeding process
void loadFood() {
    // Code to handle the feeding process
    Serial.println("Feeding cat...");
    determineFoodAmount();
    rotateReservoir();
    rotateFeedScrew();
}
