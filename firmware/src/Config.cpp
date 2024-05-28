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
JsonDocument doc;

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

// Define steppers and the pins they will use
AccelStepper stepperReservoir(AccelStepper::DRIVER, 35, 36); // Ensure these are valid pins
AccelStepper stepperScrew(AccelStepper::DRIVER, 37, 38); // Ensure these are valid pins
// define endstop pin
int endstopPin = 2;

// variables to define foodBay position in steps since its 800 steps per revolution and there are 3 foodBays
// 1st one is in angle 0, second in angle 60 and third in angle 120
int foodBay1 = 0;
// foodBay 2 is in angle 60 so it needs to move 800/360*60 = 133.33 steps
int foodBay2 = 133;
// foodBay 3 is in angle 120 so it needs to move 800/360*120 = 266.67 steps
int foodBay3 = 267;
//if I want to add more foodBays, follow the same logic 
