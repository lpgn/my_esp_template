/**
 * @file main.cpp
 * @brief Main program execution entry point.
 *
 * Initializes the system components and enters the main operation loop. This file sets up
 * network connections, server responses, and periodic tasks.
 */

#include "Config.h"

void setup() {
    Serial.begin(115200);
    setupStorage();
    configureWiFiSettings();
    scanAvailableWiFiNetworks();
    initiateWiFiConnection();
    printCompilationTimestamp();
    initializeRtc();
    initializeServer();
    serverHandle();
    initializeStepper();
     // Start the system
    setupFeeder();
}

void loop() {
    // checkFeedingSchedule();
    nonBlockingDelay(30000, checkFeedingSchedule, lastCallTime);
    // Serial.println("Loop end");
    // delay(1000); // Adding a delay to avoid potential flooding of Serial output
    // stepperScrew.run();  // Regularly call this to update stepper position and handle speed/acceleration changes
    // handleEndStop();    
    // stepperReservoir.run();  // Regularly call this to update stepper position and handle speed/acceleration changes
    // Enter the main loop
    // The ESP32 now waits passively for RFID data from the Tiny1614
    // Non-blocking delay with callback
    //wait passively for RFID read from the Tiny1614
    //check if the RFID tag is valid
    //if valid, check if the tag is in the feeding schedule
    //if in the feeding schedule, check if the feeding schedule is active
    //if active move the stepper to the food bay position
    //if not in the feeding schedule, do nothing

    }