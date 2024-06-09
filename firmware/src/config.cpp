#include "config.h"

ESP32Time rtc;
WiFiMulti wifiMulti;
AsyncWebServer server(80);
JsonDocument doc;
unsigned long lastCallTime = 0;
unsigned long lastCalibrationTime = 0;

// define pin for endstop
// this is a setup for the endstop pin
const int endStopPin = 42;

Bounce endstopDebouncer = Bounce();

const char *wifi_network_hostname = "name_hostname";
const char *soft_ap_ssid = "name_SSID";
const char *soft_ap_password = "name_password";

RtcDS3231<TwoWire> Rtc(Wire);
int sdaPin = 4;
int sclPin = 5;

//define the pins for the steppers
#define stepperReservoirDirPin 8//17
#define stepperReservoirStepPin 3//16
#define stepperScrewEnablePin 46//18

#define stepperScrewDirPin 17//8
#define stepperScrewStepPin 16//3
#define stepperScrewEnablePin 18//46

// Define steppers and the pins they will use
AccelStepper stepperReservoir(AccelStepper::DRIVER, stepperReservoirStepPin, stepperReservoirDirPin); // Ensure these are valid pins
AccelStepper stepperScrew(AccelStepper::DRIVER, stepperScrewStepPin, stepperScrewDirPin); // Ensure these are valid pins
// variables to define foodBay position in steps since its 800 steps per revolution and there are 3 foodBays
// 1st one is in angle 0, second in angle 60 and third in angle 120
int foodBay1 = 0;
// foodBay 2 is in angle 60 so it needs to move 1600/360*60 = 266.66
int foodBay2 = 266;
// foodBay 3 is in angle 120 so it needs to move 1600/360*120 = 533.33
int foodBay3 = 533;

int maxSpeedReservoir = 2500.0;
int accelerationReservoir = 5000.0;
int maxSpeedScrew = 500.0;
int accelerationScrew = 500.0;

int stepsPerGram = 40;


