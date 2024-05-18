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
    stepper.run();  // Regularly call this to update stepper position and handle speed/acceleration changes
    // Enter the main loop
    mainLoop();
    //wait passively for RFID read from the Tiny1614
}
