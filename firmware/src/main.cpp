#include "config.h"

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
    setupEndstopInterrupt(endStopPin);
    initializeStepper();
     // Start the system
    setupFeeder();
}

void loop() {
    updateEndstopState(); // Update the endstop state

    // Other tasks...
    if (checkEndstopHit()) {
        printAsciiBox("Endstop clicked!");
        // Handle endstop hit event, e.g., stop stepper or take corrective action
    }
    if (checkEndstopReleased()) {
        printAsciiBox("Endstop released!");
        // Handle endstop release event, if any action is needed
    }
    //run calibration routine every day 2 times a day
    nonBlockingDelay(43200000, calibrateReservoir, lastCalibrationTime);
    // Non-blocking delay with callback
    nonBlockingDelay(60000, checkFeedingSchedule, lastCallTime);
    // checking if Cat is at the door
    // validateCatInfo(rfidTag);
    // log cat entry
    // logCatEntry(rfidTag);
}
