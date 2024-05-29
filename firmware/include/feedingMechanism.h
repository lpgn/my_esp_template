#ifndef FEEINGMECHANISM_H
#define FEEINGMECHANISM_H

#include "config.h"

void initializeStepper(); // Initializes the stepper motors
void rotateReservoir(int foodBay); // Rotates the reservoir to the correct
void rotateFeedScrew(int stepsMotor2); // Rotates the feed screw to dispense food
void loadFood();        // Handles the entire feeding process
void myCallback();      // Callback function for non-blocking delay

#endif // FEEINGMECHANISM_H
