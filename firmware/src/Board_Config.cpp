/**
 * @file Board_Config.cpp
 * @brief Implementation of board configuration functions.
 *
 * This file implements the functions declared in Board_Config.h to initialize and manage
 * board-specific configurations and hardware setup.
 */

// Define configuration settings for different boards

#include "Board_Config.h"

const BoardConfig configs[] = {
    {
        "proto_nuts",     // Board name
       // 21,                // DHT sensor pin
       // DHT11,             // DHT sensor type (-1=None, 11=DHT11, 22=DHT22, 21=AM2301)

        "name_hostname",         // WiFi network hostname
        "name_SSID",     // Soft AP SSID
        "name_password",                 // Soft AP password
    }
    };

#ifdef ds_3231
RtcDS3231<TwoWire> Rtc(Wire);
int sdaPin = 05;
int sclPin = 17;
#endif

#ifdef ds_1302
ThreeWire myWire(14, 13, 32);
RtcDS1302<ThreeWire> Rtc(myWire);
#endif

ESP32Time rtc;