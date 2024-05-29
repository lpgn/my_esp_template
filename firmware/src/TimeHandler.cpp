#include "TimeHandler.h"
#include "Config.h"

void printCompilationTimestamp()
{
    Serial.println("*****************************************************");
    Serial.println("* Function printCompilationTimestamp()");
    Serial.printf("* Compiled on %s at %s\n\r", __DATE__, __TIME__);
    Serial.println("*****************************************************");
}


void printRtcDateTime(const RtcDateTime &dt)
{
    char datestring[20];
    snprintf_P(datestring, countof(datestring), PSTR("%02u/%02u/%04u %02u:%02u:%02u"), dt.Month(), dt.Day(), dt.Year(), dt.Hour(), dt.Minute(), dt.Second());
    Serial.print("RTC DateTime: ");
    Serial.println(datestring);
}

void syncInternalRtcWithExternal(const RtcDateTime &dt)
{
    char datestring[20];
    snprintf_P(datestring, countof(datestring), PSTR("%02u/%02u/%04u %02u:%02u:%02u"), dt.Month(), dt.Day(), dt.Year(), dt.Hour(), dt.Minute(), dt.Second());
    rtc.setTime(dt.Second(), dt.Minute(), dt.Hour(), dt.Day(), dt.Month(), dt.Year());

    Serial.println("*****************************************************");
    Serial.println("* Function syncInternalRtcWithExternal()");
    Serial.printf("* Time from external RTC: %s\n\r", datestring);
    Serial.println("* This function updates the internal RTC with the time");
    Serial.println("* from the external RTC");
    Serial.println("*****************************************************");
}

void initializeRtc()
{
    Serial.println("*****************************************************");
    Serial.println("* Running function initializeRtc()");

#ifdef ds_3231
    Wire.begin(sdaPin, sclPin);
    Serial.println("* I2C initialized for DS3231");
#endif

    Rtc.Begin();
    Serial.println("* RTC begin called");

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    Serial.print("* Time from internal RTC on boot: ");
    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S").c_str());

    RtcDateTime externalRtcTime = Rtc.GetDateTime();
    if (externalRtcTime.IsValid()) {
        syncInternalRtcWithExternal(externalRtcTime);
    } else {
        Serial.println("* Failed to get valid time from external RTC");
    }

    Serial.print("* Time from internal RTC after external RTC update: ");
    Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S").c_str());

    if (!Rtc.IsDateTimeValid())
    {
        Serial.println("* RTC lost confidence in the DateTime! Setting to compile time.");
        Rtc.SetDateTime(compiled);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("* RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled)
    {
        Serial.println("* RTC is older than compile time!  (Updating DateTime)");
        Rtc.SetDateTime(compiled);
    }
    else if (now > compiled)
    {
        Serial.println("* RTC is newer than compile time. (This is expected)");
    }
    else if (now == compiled)
    {
        Serial.println("* RTC is the same as compile time! (Not expected but all is fine)");
    }

    Serial.println("* END of data from initializeRtc()");
    Serial.println("*****************************************************");
}

void printRtcDateTimeInLoop()
{
    static unsigned long previousMillis = 0;
    const long printTimeInterval = 1000;

    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= printTimeInterval)
    {
        previousMillis = currentMillis;

        RtcDateTime now = Rtc.GetDateTime();
        if (now.IsValid())
        {
            printRtcDateTime(now);
        }
        else
        {
            Serial.println("RTC lost confidence in the DateTime!");
        }
    }
}
