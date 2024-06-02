#include <Arduino.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <AccelStepper.h>
#include <Bounce2.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>

// RTC
RtcDS3231<TwoWire> Rtc(Wire);

// Stepper Motors Pins
int dirReservoir = 2, stepReservoir = 3;
int dirScrew = 4, stepScrew = 5;
AccelStepper stepperReservoir(AccelStepper::DRIVER, stepReservoir, dirReservoir); // Default pins: DIR, STEP
AccelStepper stepperScrew(AccelStepper::DRIVER, stepScrew, dirScrew); // Default pins: DIR, STEP

// End Stop
int endStopPin = 6;
Bounce endStop = Bounce();

// Variables
int stepperReservoirPositions[3] = {0, 60, 120};
int stepperScrewSteps = 50;
bool calibrated = false;

// Web server
WebServer server(80);

void handleRoot() {
    File file = LittleFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void handleSaveSettings() {
    if (!server.hasArg("plain")) {
        server.send(400, "text/plain", "Bad Request");
        return;
    }

    String body = server.arg("plain");
    JsonDocument doc;
    deserializeJson(doc, body);

    // Parse settings
    const char* stepperReservoirPosStr = doc["stepperReservoirPos"];
    sscanf(stepperReservoirPosStr, "%d,%d,%d", &stepperReservoirPositions[0], &stepperReservoirPositions[1], &stepperReservoirPositions[2]);

    stepperScrewSteps = doc["stepperScrewSteps"];

    int newDirReservoir, newStepReservoir, newDirScrew, newStepScrew;
    sscanf(doc["stepperReservoirPins"], "%d,%d", &newDirReservoir, &newStepReservoir);
    sscanf(doc["stepperScrewPins"], "%d,%d", &newDirScrew, &newStepScrew);

    // Update pins if they have changed
    if (newDirReservoir != dirReservoir || newStepReservoir != stepReservoir) {
        dirReservoir = newDirReservoir;
        stepReservoir = newStepReservoir;
        stepperReservoir = AccelStepper(AccelStepper::DRIVER, stepReservoir, dirReservoir);
        stepperReservoir.setMaxSpeed(50);
        stepperReservoir.setAcceleration(100);
        Serial.println("Updated stepperReservoir pins");
    }

    if (newDirScrew != dirScrew || newStepScrew != stepScrew) {
        dirScrew = newDirScrew;
        stepScrew = newStepScrew;
        stepperScrew = AccelStepper(AccelStepper::DRIVER, stepScrew, dirScrew);
        stepperScrew.setMaxSpeed(50);
        stepperScrew.setAcceleration(100);
        Serial.println("Updated stepperScrew pins");
    }

    endStopPin = doc["endStopPin"];
    endStop.attach(endStopPin, INPUT_PULLUP);

    server.send(200, "text/plain", "Settings Saved");
    Serial.println("Settings saved");

    // Reset calibration since pins might have changed
    calibrated = false;
}

// Function Prototypes
void calibrateReservoir();
void performTask();

void setup() {
    Serial.begin(115200);
    Wire.begin();
    Rtc.Begin();

    // Set up LittleFS
    if (!LittleFS.begin()) {
        Serial.println("An error has occurred while mounting LittleFS");
        return;
    }
    Serial.println("LittleFS mounted successfully");

    // Set up WiFi
    WiFi.begin("quarto_casal", "imgrumpy");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Set up web server
    server.on("/", handleRoot);
    server.on("/saveSettings", HTTP_POST, handleSaveSettings);
    server.begin();
    Serial.println("Web server started");

    // Set end stop pin
    pinMode(endStopPin, INPUT_PULLUP);
    endStop.attach(endStopPin);
    endStop.interval(10);

    // Stepper motor setup
    stepperReservoir.setMaxSpeed(50);
    stepperReservoir.setAcceleration(100);

    stepperScrew.setMaxSpeed(50);
    stepperScrew.setAcceleration(100);

    Serial.println("Setup completed");
}

void loop() {
    server.handleClient();

    RtcDateTime now = Rtc.GetDateTime();
    endStop.update();

    if (!calibrated) {
        Serial.println("Calibrating reservoir...");
        calibrateReservoir();
        Serial.println("Reservoir calibrated");
    }

    if (now.Hour() == 8 && now.Minute() == 0 && now.Second() == 0) {
        Serial.println("Performing task at 8 AM");
        performTask();
    } else if (now.Hour() == 18 && now.Minute() == 0 && now.Second() == 0) {
        Serial.println("Performing task at 6 PM");
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
        Serial.print("Moved stepperReservoir to position ");
        Serial.println(stepperReservoirPositions[i]);

        stepperScrew.move(stepperScrewSteps);
        while (stepperScrew.distanceToGo() != 0) {
            stepperScrew.run();
        }
        Serial.print("Moved stepperScrew by ");
        Serial.print(stepperScrewSteps);
        Serial.println(" steps");
    }
}
