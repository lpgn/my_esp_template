#include "timeHandler.h"

bool getCurrentTime(char* currentTime, size_t size) {
    RtcDateTime now = Rtc.GetDateTime();
    if (!now.IsValid()) {
        Serial.println("Failed to retrieve valid time from RTC.");
        return false;
    }
    snprintf(currentTime, size, "%02d:%02d", now.Hour(), now.Minute());
    return true;
}

void printCompilationTimestamp() {
    String message = "Compiled on " + String(__DATE__) + " at " + String(__TIME__);
    printAsciiBox(message);
}

void printRtcDateTime(const RtcDateTime &dt) {
    char datestring[20];
    snprintf_P(datestring, sizeof(datestring), PSTR("%02u/%02u/%04u %02u:%02u:%02u"), dt.Month(), dt.Day(), dt.Year(), dt.Hour(), dt.Minute(), dt.Second());
    Serial.print("RTC DateTime: ");
    Serial.println(datestring);
}

void syncInternalRtcWithExternal(const RtcDateTime &dt) {
    char datestring[20];
    snprintf_P(datestring, sizeof(datestring), PSTR("%02u/%02u/%04u %02u:%02u:%02u"), dt.Month(), dt.Day(), dt.Year(), dt.Hour(), dt.Minute(), dt.Second());
    rtc.setTime(dt.Second(), dt.Minute(), dt.Hour(), dt.Day(), dt.Month(), dt.Year());

    String message = "External RTC: " + String(datestring) + "\nInternal RTC updated";
    printAsciiBox(message);
}

void initializeRtc() {
    printAsciiBox("Initializing RTC");

    Wire.begin(sdaPin, sclPin);
    Serial.println("* I2C initialized for DS3231");
    
    Rtc.Begin();
    Serial.println("* RTC started");

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    Serial.print("* Internal RTC on boot: ");
    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S").c_str());

    RtcDateTime externalRtcTime = Rtc.GetDateTime();
    if (externalRtcTime.IsValid()) {
        syncInternalRtcWithExternal(externalRtcTime);
    } else {
        Serial.println("* Invalid time from external RTC");
    }

    Serial.print("* Internal RTC after update: ");
    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S").c_str());

    if (!Rtc.IsDateTimeValid()) {
        Serial.println("* Invalid DateTime, setting compile time");
        Rtc.SetDateTime(compiled);
    }

    if (!Rtc.GetIsRunning()) {
        Serial.println("* RTC not running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) {
        Serial.println("* RTC older than compile time, updating");
        Rtc.SetDateTime(compiled);
    } else if (now > compiled) {
        Serial.println("* RTC newer than compile time");
    } else if (now == compiled) {
        Serial.println("* RTC matches compile time");
    }

    printAsciiBox("RTC Initialization Complete");
}

void printRtcDateTimeInLoop() {
    static unsigned long previousMillis = 0;
    const long printTimeInterval = 1000;

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= printTimeInterval) {
        previousMillis = currentMillis;

        RtcDateTime now = Rtc.GetDateTime();
        if (now.IsValid()) {
            printRtcDateTime(now);
        } else {
            Serial.println("RTC DateTime invalid!");
        }
    }
}
