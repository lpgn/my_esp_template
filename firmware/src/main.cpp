#include <Arduino.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <FastAccelStepper.h>
#include <Bounce2.h>

// Define the pins for SDA and SCL
#define SDA 4
#define SCL 5

// RTC
RtcDS3231<TwoWire> Rtc(Wire);

// Stepper Motors
// DIR, STEP, enable pins
#define DIR_PIN_RESERVOIR 13
#define STEP_PIN_RESERVOIR 40
#define ENABLE_PIN_RESERVOIR 7

#define DIR_PIN_SCREW 37
#define STEP_PIN_SCREW 38
#define ENABLE_PIN_SCREW 21

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepperReservoir = NULL;
FastAccelStepper *stepperScrew = NULL;

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
void initialStepperMovement();

void setup() {
    delay(5000); // 30 seconds delay to allow the serial monitor to connect
    Serial.begin(115200);
    Wire.begin();
    Rtc.Begin();
    // Print time on one line with one line of code on the serial monitor
    printCurrentTime();

    // Set end stop pin
    pinMode(endStopPin, INPUT_PULLUP);
    endStop.attach(endStopPin);
    endStop.interval(50);

    // Initialize stepper engine and stepper motors
    engine.init();
    stepperReservoir = engine.stepperConnectToPin(STEP_PIN_RESERVOIR);
    stepperScrew = engine.stepperConnectToPin(STEP_PIN_SCREW);

    if (stepperReservoir) {
        stepperReservoir->setDirectionPin(DIR_PIN_RESERVOIR);
        stepperReservoir->setEnablePin(ENABLE_PIN_RESERVOIR);
        stepperReservoir->setAutoEnable(true);
        stepperReservoir->setSpeedInHz(100);  // Set speed in Hz
        stepperReservoir->setAcceleration(100);
    }

    if (stepperScrew) {
        stepperScrew->setDirectionPin(DIR_PIN_SCREW);
        stepperScrew->setEnablePin(ENABLE_PIN_SCREW);
        stepperScrew->setAutoEnable(true);
        stepperScrew->setSpeedInHz(100);  // Set speed in Hz
        stepperScrew->setAcceleration(100);
    }

    // Perform initial stepper movement
    initialStepperMovement();

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
    stepperReservoir->moveTo(-100000); // move a large negative number to ensure reaching end stop
    while (!endStop.read()) {
        stepperReservoir->runForward();
    }
    stepperReservoir->forceStopAndNewPosition(0);
    calibrated = true;
    Serial.println("Reservoir calibrated.");
    printCurrentTime();
}

void performTask() {
    for (int i = 0; i < 3; i++) {
        Serial.print("Moving reservoir to position ");
        Serial.print(stepperReservoirPositions[i]);
        Serial.println("...");
        stepperReservoir->moveTo(stepperReservoirPositions[i]);
        while (stepperReservoir->isRunning()) {
            // Waiting for the stepper to reach the target position
        }
        Serial.println("Reservoir in position.");

        Serial.print("Moving screw for quantity ");
        Serial.print(stepperScrewSteps[i]);
        Serial.println("...");
        stepperScrew->move(stepperScrewSteps[i]);
        while (stepperScrew->isRunning()) {
            // Waiting for the stepper to finish the move
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

void initialStepperMovement() {
    Serial.println("Performing initial stepper movement...");

    // Move stepperReservoir 50 steps to each side
    stepperReservoir->move(50);
    while (stepperReservoir->isRunning()) {
        // Waiting for the stepper to complete the move
    }
    delay(500); // Small delay between movements
    stepperReservoir->move(-50);
    while (stepperReservoir->isRunning()) {
        // Waiting for the stepper to complete the move
    }

    // Move stepperScrew 50 steps to each side
    stepperScrew->move(50);
    while (stepperScrew->isRunning()) {
        // Waiting for the stepper to complete the move
    }
    delay(500); // Small delay between movements
    stepperScrew->move(-50);
    while (stepperScrew->isRunning()) {
        // Waiting for the stepper to complete the move
    }

    Serial.println("Initial stepper movement complete.");
}
