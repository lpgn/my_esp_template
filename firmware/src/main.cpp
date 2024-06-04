#include <Arduino.h>
#include <WiFi.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <FastAccelStepper.h>
#include <Bounce2.h>

// WiFi credentials
const char *ssid = "ratinho_do_malandro";
const char *password = "newgerryforever2018";

// Define the pins for SDA and SCL
#define SDA 4
#define SCL 5

// Stepper Motors
// DIR, STEP, enable pins
#define DIR_PIN_RESERVOIR 8
#define STEP_PIN_RESERVOIR 3
#define ENABLE_PIN_RESERVOIR 46

#define DIR_PIN_SCREW 17
#define STEP_PIN_SCREW 16
#define ENABLE_PIN_SCREW 18

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepperReservoir = NULL;
FastAccelStepper *stepperScrew = NULL;

// End Stop
const int endStopPin = 42;
Bounce endStop = Bounce();

// NTP Client
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 0, 60000); // Update every minute

// Variables
int modulo_gumble = 0;
int modulo_Gerry = 720;
int modulo_Pipoca = 960;
const int stepperReservoirPositions[] = {modulo_gumble, modulo_Gerry, modulo_Pipoca};

int quantidade_Gumble = 400;
int quantidade_Gerry = 720;
int quantidade_Pipoca = 400;
const int stepperScrewSteps[] = {quantidade_Gumble, quantidade_Gerry, quantidade_Pipoca};
bool calibrated = false;

// Function Prototypes
void calibrateReservoir();
void performTask();
void printCurrentTime();
void initialStepperMovement();
void connectToWiFi();

void setup() {
    delay(5000); // Delay to allow the serial monitor to connect
    Serial.begin(115200);

    connectToWiFi();
    timeClient.begin();

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
        stepperReservoir->setSpeedInHz(500);  // Set speed in Hz
        stepperReservoir->setAcceleration(500);
    }

    if (stepperScrew) {
        stepperScrew->setDirectionPin(DIR_PIN_SCREW);
        stepperScrew->setEnablePin(ENABLE_PIN_SCREW);
        stepperScrew->setAutoEnable(true);
        stepperScrew->setSpeedInHz(500);  // Set speed in Hz
        stepperScrew->setAcceleration(500);
    }

    // Perform initial stepper movement
    initialStepperMovement();

    performTask();
}

void loop() {
    timeClient.update();
    endStop.update();

    if (!calibrated) {
        calibrateReservoir();
    }

    int currentHour = timeClient.getHours();
    int currentMinute = timeClient.getMinutes();
    int currentSecond = timeClient.getSeconds();

    if ((currentHour == 8 && currentMinute == 0 && currentSecond == 0) || 
        (currentHour == 18 && currentMinute == 0 && currentSecond == 0)) {
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
    Serial.print("Current time: ");
    Serial.print(timeClient.getFormattedTime());
    Serial.println();
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

void connectToWiFi() {
    Serial.print("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(" connected!");
}
