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
}

void loop() {

    // Run routine every x ms
    // nonBlockingDelay(43200000, the_function, lastCalibrationTime);

}
