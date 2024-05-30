#include "stepperMove.h"

void initializeStepper() {
   //note to self: add the correct values for the max speed and acceleration
    stepperReservoir.setMaxSpeed(maxSpeedReservoir);
    stepperReservoir.setAcceleration(accelerationReservoir);
    stepperScrew.setMaxSpeed(maxSpeedScrew);
    stepperScrew.setAcceleration(accelerationScrew);
}

void moveReservoir(int modulePosition) {
    // Logic to move the reservoir to the correct module position
    stepperReservoir.moveTo(modulePosition);
    stepperReservoir.runToPosition();
}

void moveScrew(int amount) {
    // Logic to move the screw and dispense food
    stepperScrew.moveTo(amount); 
    stepperScrew.runToPosition();
}