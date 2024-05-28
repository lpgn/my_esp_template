/**
 * @file Config.cpp
 * @brief Implementation of global configuration variables.
 *
 * Defines and initializes configuration parameters used across the project. This implementation
 * helps in isolating configuration management from business logic.
 */

#include "Config.h"

ESP32Time rtc;

WiFiMulti wifiMulti;
AsyncWebServer server(80);

const char *wifi_network_hostname = "name_hostname";
const char *soft_ap_ssid = "name_SSID";
const char *soft_ap_password = "name_password";

#ifdef ds_3231
RtcDS3231<TwoWire> Rtc(Wire);
int sdaPin = 5;
int sclPin = 4;
#endif

#ifdef ds_1302
ThreeWire myWire(14, 13, 32);
RtcDS1302<ThreeWire> Rtc(myWire);
#endif

