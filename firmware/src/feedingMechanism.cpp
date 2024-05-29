//feeding mechanism code
//This code is responsible for the feeding mechanism of the cat feeder
//It includes the functions to initialize the stepper motors, determine the food amount, 
//rotate the reservoir, rotate the feed screw, and handle the entire feeding process

#include "feedingMechanism.h"

void initializeStepper() {
   //note to self: add the correct values for the max speed and acceleration
    stepperReservoir.setMaxSpeed(maxSpeedReservoir);
    stepperReservoir.setAcceleration(accelerationReservoir);
    stepperScrew.setMaxSpeed(maxSpeedScrew);
    stepperScrew.setAcceleration(accelerationScrew);
}
