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
AccelStepper stepperReservoir(AccelStepper::DRIVER, 13, 40); // DIR, STEP pins
AccelStepper stepperScrew(AccelStepper::DRIVER, 37, 38); // DIR, STEP pins

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

void setup() {
    delay(30000); // 30 seconds delay to allow the serial monitor to connect
    Serial.begin(115200);
    Wire.begin();
    Rtc.Begin();
    //PRINT TIME ON ONE LINE WITH ONE LINE OF CODE ON SERIAL MONITOR
    Serial.println(Rtc.GetDateTime().Epoch32Time());



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

        stepperScrew.move(stepperScrewSteps[i]);
        while (stepperScrew.distanceToGo() != 0) {
            stepperScrew.run();
        }
    }
}
