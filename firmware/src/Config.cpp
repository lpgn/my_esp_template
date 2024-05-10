#include "Config.h"

/**
 * @file Config.cpp
 * @brief Implementation of global configuration variables.
 *
 * Defines and initializes configuration parameters used across the project. This implementation
 * helps in isolating configuration management from business logic.
 */

const char *wifi_network_hostname = BOARD_CONFIG.wifi_hostname;
const char *soft_ap_ssid = BOARD_CONFIG.ap_ssid;
const char *soft_ap_password = BOARD_CONFIG.ap_password;


AsyncWebServer server(80);
WiFiMulti wifiMulti;
