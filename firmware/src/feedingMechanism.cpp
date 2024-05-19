//feeding mechanism code
//This code is responsible for the feeding mechanism of the cat feeder
//It includes the functions to initialize the stepper motors, determine the food amount, 
//rotate the reservoir, rotate the feed screw, and handle the entire feeding process

#include "feedingMechanism.h"

int foodAmount = 100; // Amount of food to dispense in grams
int stepsMotor2 = foodAmount * 10; // Steps per gram for X amount of food

void initializeStepper() {
   //note to self: add the correct values for the max speed and acceleration
    stepperReservoir.setMaxSpeed(100000.0); 
    stepperReservoir.setAcceleration(2000.0); 
    stepperScrew.setMaxSpeed(100000.0);
    stepperScrew.setAcceleration(2000.0);
}


void loadFood() {
    // Code to handle the feeding process
    Serial.println("Feeding cat...");
    determineFoodAmount("Cat Name", 100); // Pass the required arguments to the function call
    rotateReservoir(1); // Pass the required argument to the function call
    rotateFeedScrew(100); // Pass the required argument to the function call
}

int determineFoodAmount(const String& catName, int foodAmount) {
    // Example calculations - replace with your actual logic

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
void rotateReservoir(int foodBay) {
    // Code to rotate the reservoir based on the foodBay number
    Serial.print("Rotating reservoir to position for foodBay: ");
    Serial.println(foodBay);
    // Add logic to determine the position based on the foodBay number
    int position = 0;
    switch (foodBay) {
        case 1:
            // Code to rotate to position for foodBay 1
            position = foodBay1;
            break;
        case 2:
            // Code to rotate to position for foodBay 2
            position = foodBay2;
            break;
        case 3:
            // Code to rotate to position for foodBay 3
            position = foodBay3;
            break;
        default:
            // Code to handle unknown foodBay number
            Serial.println("Unknown foodBay number");
            return;
    }
    stepperReservoir.moveTo(position);
    while (stepperReservoir.distanceToGo() != 0) {
        stepperReservoir.run();
    }
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

