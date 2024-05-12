/**
 * @file Config.h
 * @brief Project-wide configuration parameters.
 *
 * Central configuration file for storing all adjustable parameters like network credentials,
 * server settings, and operational thresholds. Modify these parameters to customize project behavior.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>
#include <ESP32Time.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <ThreeWire.h>
#include <RtcDS1302.h>
#include <ElegantOTA.h>
#include <ESPAsyncWebServer.h>
#include <AccelStepper.h>

//include all files here
#include "WebServerManager.h"
#include "WiFiHandler.h"
#include "storageHandler.h"
#include "TimeHandler.h"
#include "stepperMove.h"

extern ESP32Time rtc;

extern WiFiMulti wifiMulti;
extern AsyncWebServer server;

extern const char *wifi_network_hostname;
extern const char *soft_ap_ssid;
extern const char *soft_ap_password;

// Define some steppers and the pins the will use
extern AccelStepper stepper;

#define ds_3231

#ifdef ds_3231
extern RtcDS3231<TwoWire> Rtc;
extern int sdaPin;
extern int sclPin;
#endif
#ifdef ds_1302
extern ThreeWire myWire;
extern RtcDS1302<ThreeWire> Rtc;
#endif

#endif // CONFIG_H