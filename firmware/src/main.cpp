/**
 * @file main.cpp
 * @brief Main program execution entry point.
 *
 * Initializes the system components and enters the main operation loop. This file sets up
 * network connections, server responses, and periodic tasks.
 */

#include "Config.h"

void setup() {
    // Initialization code here

    Serial.begin(115200);
    setupStorage();
    configureWiFiSettings();
    scanAvailableWiFiNetworks();
    initiateWiFiConnection();
    printCompilationTimestamp();
    initializeRtc();
    initializeServer();
    serverHandle();
    moveStepper();
    stepperToggle(); // Check and toggle direction as needed
    stepper.run();   // Regularly update the stepper's operation
}

void loop() {
    stepper.run();  // Regularly call this to update stepper position and handle speed/acceleration changes
}
