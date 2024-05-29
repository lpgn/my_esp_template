/**
 * @file .cpp
 * @brief Implementation of global configuration variables.
 *
 * Defines and initializes configuration parameters used across the project. This implementation
 * helps in isolating configuration management from business logic.
 */

#include "config.h"

ESP32Time rtc;
WiFiMulti wifiMulti;
AsyncWebServer server(80);
JsonDocument doc;
unsigned long lastCallTime = 0;

// define pin for endstop
// this is a setup for the endstop pin
const int endStopPin = 42;


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

//define the pins for the steppers
#define stepperReservoirStepPin 38
#define stepperReservoirDirPin 37
#define stepperScrewStepPin 39
#define stepperScrewDirPin 40

// Define steppers and the pins they will use
AccelStepper stepperReservoir(AccelStepper::DRIVER, stepperReservoirStepPin, stepperReservoirDirPin); // Ensure these are valid pins
AccelStepper stepperScrew(AccelStepper::DRIVER, stepperScrewStepPin, stepperScrewDirPin); // Ensure these are valid pins
// define endstop pin
int endstopPin = 2;

// variables to define foodBay position in steps since its 800 steps per revolution and there are 3 foodBays
// 1st one is in angle 0, second in angle 60 and third in angle 120
int foodBay1 = 0;
// foodBay 2 is in angle 60 so it needs to move 200/360*60 = 33.33
int foodBay2 = 33;
// foodBay 3 is in angle 120 so it needs to move 200/360*120 = 66.66
int foodBay3 = 67;
//if I want to add more foodBays, follow the same logic 

int maxSpeedReservoir = 50.0;
int accelerationReservoir = 100.0;
int maxSpeedScrew = 50.0;
int accelerationScrew = 100.0;

int stepsPerGram = 1000;


