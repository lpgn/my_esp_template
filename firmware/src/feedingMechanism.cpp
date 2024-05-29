#include "feedingMechanism.h"

void initializeStepper() {
   //note to self: add the correct values for the max speed and acceleration
    stepperReservoir.setMaxSpeed(maxSpeedReservoir);
    stepperReservoir.setAcceleration(accelerationReservoir);
    stepperScrew.setMaxSpeed(maxSpeedScrew);
    stepperScrew.setAcceleration(accelerationScrew);
}
