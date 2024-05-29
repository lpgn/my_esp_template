#ifndef SETUP_CAT_FEEDER_H
#define SETUP_CAT_FEEDER_H

#include "Config.h"

// Function declarations
void setupFeeder(); // Setup feeder system
void calibrateReservoir(); // Calibrate the reservoir position
void moveReservoir(int modulePosition); // Move the reservoir
void moveScrew(int amount); // Move the screw
#endif // SETUP_CAT_FEEDER_H