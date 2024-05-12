/**
 * @file Board_Config.cpp
 * @brief Implementation of board configuration functions.
 *
 * This file implements the functions declared in Board_Config.h to initialize and manage
 * board-specific configurations and hardware setup.
 */

// Define configuration settings for different boards

#include "Board_Config.h"

const char *name = "proto_nuts";     // Board name
const char *wifi_hostname = "name_hostname";         // WiFi network hostname
const char *ap_ssid = "name_SSID";     // Soft AP SSID
const char *ap_password = "name_password";                 // Soft AP password

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