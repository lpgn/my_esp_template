#ifndef FEEINGMECHANISM_H
#define FEEINGMECHANISM_H

#include "Config.h"

void initializeStepper() // Initializes the stepper motors
void determineFoodAmount(const String& catName, int foodAmount); // Determines the required amount of food
void rotateReservoir(); // Rotates the reservoir to the correct position
void rotateFeedScrew(); // Rotates the feed screw to dispense food
void loadFood(); // Handles the entire feeding process

#endif // FEEINGMECHANISM_H
