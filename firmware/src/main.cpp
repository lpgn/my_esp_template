#include <Arduino.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <AccelStepper.h>
#include <Bounce2.h>

// Define the pins for SDA and SCL
#define SDA 4
#define SCL 5

// RTC
RtcDS3231<TwoWire> Rtc(Wire);

// Stepper Motors
// DIR, STEP, enable pins
AccelStepper stepperReservoir(AccelStepper::DRIVER, 13, 40, 12);
// DIR, STEP,enable pins
AccelStepper stepperScrew(AccelStepper::DRIVER, 37, 38, 36);

// End Stop
const int endStopPin = 42;
Bounce endStop = Bounce();

// Variables
int modulo_gumble = 0;
int modulo_Gerry = 60;
int modulo_Pipoca = 120;
const int stepperReservoirPositions[] = {modulo_gumble, modulo_Gerry, modulo_Pipoca};

int quantidade_Gumble = 50;
int quantidade_Gerry = 60;
int quantidade_Pipoca = 50;
const int stepperScrewSteps[] = {quantidade_Gumble, quantidade_Gerry, quantidade_Pipoca};
bool calibrated = false;

// Function Prototypes
void calibrateReservoir();
void performTask();
void printCurrentTime();

void setup() {
    delay(30000); // 30 seconds delay to allow the serial monitor to connect
    Serial.begin(115200);
    Wire.begin();
    Rtc.Begin();
    // Print time on one line with one line of code on the serial monitor
    printCurrentTime();

    // Set end stop pin
    pinMode(endStopPin, INPUT_PULLUP);
    endStop.attach(endStopPin);
    endStop.interval(50);

    // Stepper motor setup
    stepperReservoir.setMaxSpeed(50);
    stepperReservoir.setAcceleration(100);

    stepperScrew.setMaxSpeed(50);
    stepperScrew.setAcceleration(100);

    performTask();
}

void loop() {
    RtcDateTime now = Rtc.GetDateTime();
    endStop.update();

    if (!calibrated) {
        calibrateReservoir();
    }

    if ((now.Hour() == 8 && now.Minute() == 0 && now.Second() == 0) || 
        (now.Hour() == 18 && now.Minute() == 0 && now.Second() == 0)) {
        Serial.println("Performing scheduled task:");
        printCurrentTime();
        performTask();
    }
}

void calibrateReservoir() {
    Serial.println("Calibrating reservoir...");
    stepperReservoir.moveTo(-1);
    while (!endStop.read()) {
        stepperReservoir.run();
    }
    stepperReservoir.setCurrentPosition(0);
    calibrated = true;
    Serial.println("Reservoir calibrated.");
    printCurrentTime();
}

void performTask() {
    for (int i = 0; i < 3; i++) {
        Serial.print("Moving reservoir to position ");
        Serial.print(stepperReservoirPositions[i]);
        Serial.println("...");
        stepperReservoir.moveTo(stepperReservoirPositions[i]);
        while (stepperReservoir.distanceToGo() != 0) {
            stepperReservoir.run();
        }
        Serial.println("Reservoir in position.");

        Serial.print("Moving screw for quantity ");
        Serial.print(stepperScrewSteps[i]);
        Serial.println("...");
        stepperScrew.move(stepperScrewSteps[i]);
        while (stepperScrew.distanceToGo() != 0) {
            stepperScrew.run();
        }
        Serial.println("Screw movement complete.");
    }
    Serial.println("Task completed.");
    printCurrentTime();
}

void printCurrentTime() {
    RtcDateTime now = Rtc.GetDateTime();
    char timeBuffer[20];
    snprintf(timeBuffer, sizeof(timeBuffer), "%04u-%02u-%02u %02u:%02u:%02u", 
             now.Year(), now.Month(), now.Day(), now.Hour(), now.Minute(), now.Second());
    Serial.println(timeBuffer);
}
