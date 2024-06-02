#include <Arduino.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <AccelStepper.h>
#include <Bounce2.h>

// RTC
RtcDS3231<TwoWire> Rtc(Wire);

// Stepper Motors
AccelStepper stepperReservoir(AccelStepper::DRIVER, 2, 3); // DIR, STEP pins
AccelStepper stepperScrew(AccelStepper::DRIVER, 4, 5); // DIR, STEP pins

// End Stop
const int endStopPin = 6;
Bounce endStop = Bounce();

// Variables
const int stepperReservoirPositions[] = {0, 60, 120};
const int stepperScrewSteps = 50;
bool calibrated = false;

// Function Prototypes
void calibrateReservoir();
void performTask();

void setup() {
    Serial.begin(115200);
    Wire.begin();
    Rtc.Begin();

    // Set end stop pin
    pinMode(endStopPin, INPUT_PULLUP);
    endStop.attach(endStopPin);
    endStop.interval(50);

    // Stepper motor setup
    stepperReservoir.setMaxSpeed(1000);
    stepperReservoir.setAcceleration(500);

    stepperScrew.setMaxSpeed(1000);
    stepperScrew.setAcceleration(500);
}

void loop() {
    RtcDateTime now = Rtc.GetDateTime();
    endStop.update();

    if (!calibrated) {
        calibrateReservoir();
    }

    if (now.Hour() == 8 && now.Minute() == 0 && now.Second() == 0) {
        performTask();
    } else if (now.Hour() == 18 && now.Minute() == 0 && now.Second() == 0) {
        performTask();
    }
}

void calibrateReservoir() {
    stepperReservoir.moveTo(-1);
    while (!endStop.read()) {
        stepperReservoir.run();
    }
    stepperReservoir.setCurrentPosition(0);
    calibrated = true;
}

void performTask() {
    for (int i = 0; i < 3; i++) {
        stepperReservoir.moveTo(stepperReservoirPositions[i]);
        while (stepperReservoir.distanceToGo() != 0) {
            stepperReservoir.run();
        }

        stepperScrew.move(stepperScrewSteps);
        while (stepperScrew.distanceToGo() != 0) {
            stepperScrew.run();
        }
    }
}
