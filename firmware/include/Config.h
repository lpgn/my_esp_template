#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file Config.h
 * @brief Project-wide configuration parameters.
 *
 * Central configuration file for storing all adjustable parameters like network credentials,
 * server settings, and operational thresholds. Modify these parameters to customize project behavior.
 */

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <AsyncJson.h>

#include <ESP32Time.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <ElegantOTA.h>

//include all files here
#include "Board_Config.h"
#include "WebServerManager.h"
#include "WiFiHandler.h"
#include "storageHandler.h"
#include "TimeHandler.h"

extern WiFiMulti wifiMulti;


#define BOARD_CONFIG configs[1]

extern const char *wifi_network_hostname;
extern const char *soft_ap_ssid;
extern const char *soft_ap_password;

#define countof(a) (sizeof(a) / sizeof(a[0]))

extern ESP32Time rtc;
extern AsyncWebServer server;

#endif // CONFIG_H