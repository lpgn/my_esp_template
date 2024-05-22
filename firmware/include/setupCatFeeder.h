#ifndef SETUP_CAT_FEEDER_H
#define SETUP_CAT_FEEDER_H

#include "Config.h"

// Function declarations
void setupFeeder(); // Setup feeder system
void calibrateReservoir(); // Calibrate the reservoir position
void loadFeedingSchedule(); // Load the feeding schedule
void checkFeedingSchedule(); // Check the feeding schedule
void checkIfAlreadyAte(); // Check if the cat has already eaten

#endif // SETUP_CAT_FEEDER_H