#include "config.h"

void setup() {
    Serial.begin(115200);
    setupStorage();
    configureWiFiSettings();
    scanAvailableWiFiNetworks();
    initiateWiFiConnection();
    initializeRtc();
    initializeServer();
    serverHandle();
    setupEndstopInterrupt(endStopPin);
    initializeStepper();
    setupFeeder(); // Start the system
}

void loop() {

    // Run calibration routine every day 2 times a day
    nonBlockingDelay(43200000, calibrateReservoir, lastCalibrationTime);
    // Non-blocking delay with callback
    nonBlockingDelay(60000, checkFeedingSchedule, lastCallTime);
    
    // checking if Cat is at the door
    // validateCatInfo(rfidTag);
    // log cat entry
    // logCatEntry(rfidTag);
}
