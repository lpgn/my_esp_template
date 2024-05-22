#ifndef FEEINGMECHANISM_H
#define FEEINGMECHANISM_H

#include "Config.h"

void initializeStepper(); // Initializes the stepper motors
int determineFoodAmount(const String& catName, int foodAmount); // Determines the required amount of food
void rotateReservoir(int foodBay); // Rotates the reservoir to the correct
void rotateFeedScrew(int stepsMotor2); // Rotates the feed screw to dispense food
void loadFood();        // Handles the entire feeding process
void myCallback();      // Callback function for non-blocking delay

#endif // FEEINGMECHANISM_H
