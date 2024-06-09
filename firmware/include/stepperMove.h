#ifndef STEPPER_MOVE_H
#define STEPPER_MOVE_H

#include "config.h"

void initializeStepper(); // Initializes the stepper motors
void moveReservoir(int modulePosition);
void moveScrew(int amount);


#endif
