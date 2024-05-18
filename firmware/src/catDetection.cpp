//cat detection code
#include "catDetection.h"


void validateCatInfo(String rfidTag) {
   // Code to validate cat's information
    Serial.println("Validating cat information...");
    Serial.println("RFID Tag: " + rfidTag);
    logCatEntry(rfidTag);
    openDoor();
}

void logCatEntry(String rfidTag) {
    // Code to log cat's entry
    Serial.println("Logging cat entry...");
}

