#include "timeHandler.h"

// Function to format date and time
void formatDateTime(const RtcDateTime &dt, char* buffer, size_t size) {
    snprintf_P(buffer, size, PSTR("%02u/%02u/%04u %02u:%02u:%02u"), 
               dt.Month(), dt.Day(), dt.Year(), dt.Hour(), dt.Minute(), dt.Second());
}

// Function to synchronize internal RTC with external RTC
void syncInternalRtcWithExternal(const RtcDateTime &dt) {
    char datestring[20];
    formatDateTime(dt, datestring, sizeof(datestring));
    rtc.setTime(dt.Second(), dt.Minute(), dt.Hour(), dt.Day(), dt.Month(), dt.Year());
    printAsciiBox("External RTC: " + String(datestring) + "\nInternal RTC updated");
}

// Function to initialize the RTC
void initializeRtc() {
    printCompileTime();
    printAsciiBox("Initializing RTC");

    // Initialize I2C communication
    Wire.begin(sdaPin, sclPin);
    Serial.println("* I2C initialized for DS3231");

    // Start the external RTC
    Rtc.Begin();
    Serial.println("* External RTC started");

    // Get compile time as RtcDateTime
    RtcDateTime compiled(__DATE__, __TIME__);

    // Print internal RTC time at boot
    Serial.println("* Internal RTC on boot: " + rtc.getTime("%A, %B %d %Y %H:%M:%S"));

    // Synchronize internal RTC with external RTC if valid
    RtcDateTime externalRtcTime = Rtc.GetDateTime();
    if (externalRtcTime.IsValid()) {
        syncInternalRtcWithExternal(externalRtcTime);
    } else {
        Serial.println("* Invalid time from external RTC");
    }

    // Print internal RTC time after update
    Serial.println("* Internal RTC after update: " + rtc.getTime("%A, %B %d %Y %H:%M:%S"));

    // Validate and set the internal RTC time
    if (!Rtc.IsDateTimeValid()) {
        Serial.println("* Invalid DateTime, setting compile time");
        Rtc.SetDateTime(compiled);
    }

    // Ensure RTC is running
    if (!Rtc.GetIsRunning()) {
        Serial.println("* RTC not running, starting now");
        Rtc.SetIsRunning(true);
    }

    // Compare and update RTC time if needed
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) {
        Serial.println("* RTC older than compile time, updating");
        Rtc.SetDateTime(compiled);
    } else if (now > compiled) {
        Serial.println("* RTC newer than compile time");
    } else {
        Serial.println("* RTC matches compile time");
    }

    printAsciiBox("RTC Initialization Complete");
}
void printCompileTime()
{
    // Print compilation time
    printAsciiBox("Compiled on " + String(__DATE__) + " at " + String(__TIME__));
}

// Function to get the current time as a string
bool getCurrentTime(char* currentTime, size_t size) {
    RtcDateTime now = Rtc.GetDateTime();
    if (!now.IsValid()) {
        Serial.println("Failed to retrieve valid time from RTC.");
        return false;
    }
    snprintf(currentTime, size, "%02d:%02d", now.Hour(), now.Minute());
    return true;
}
