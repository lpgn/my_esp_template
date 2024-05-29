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
#include <AsyncJson.h>
#include <ArduinoJson.h>

// Include all necessary files here
#include "webServerManager.h"
#include "wiFiHandler.h"
#include "storageHandler.h"
#include "timeHandler.h"
#include "stepperMove.h"
#include "templates.tpp"
#include "handleEndstop.h"
#include "communication.h"
#include "catDetection.h"
#include "setupCatFeeder.h"
#include "feedingMechanism.h"
#include "scheduleHandler.h"
#include "jsonHandler.h"


extern ESP32Time rtc;
extern WiFiMulti wifiMulti;
extern AsyncWebServer server;
extern JsonDocument doc;
extern unsigned long lastCallTime;

extern const int endStopPin;

extern const char *wifi_network_hostname;
extern const char *soft_ap_ssid;
extern const char *soft_ap_password;

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


extern AccelStepper stepperReservoir;
extern AccelStepper stepperScrew;
extern int endstopPin;

extern int foodBay1;
extern int foodBay2;
extern int foodBay3;

extern int maxSpeedReservoir;
extern int accelerationReservoir;
extern int maxSpeedScrew;
extern int accelerationScrew;

extern int foodAmount;
extern int stepsMotor2;

#endif
