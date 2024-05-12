/**
 * @file Config.cpp
 * @brief Implementation of global configuration variables.
 *
 * Defines and initializes configuration parameters used across the project. This implementation
 * helps in isolating configuration management from business logic.
 */

#include "Config.h"

const char *wifi_network_hostname = wifi_hostname;
const char *soft_ap_ssid = ap_ssid;
const char *soft_ap_password = ap_password;

AsyncWebServer server(80);
WiFiMulti wifiMulti;
