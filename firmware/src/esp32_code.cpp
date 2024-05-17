
#include <Arduino.h>
#include <Wire.h>

// Function declarations
void setupFedeer();
void calibrateReservoir();
void initializeRTC();
void loadFeedingSchedule();
void checkFeedingSchedule();
void checkIfAlreadyAte();
void validateCatInfo(String rfidTag);
void logCatEntry(String rfidTag);
void openDoor();
void determineFoodAmount();
void rotateReservoir();
void rotateFeedScrew();
void loadFood();
void mainLoop();
void receiveEvent(int howMany);

// Function definitions

void setup() {
    // Initialize serial communication
    Serial.begin(115200);

    // Initialize RTC (only once)
    initializeRTC();

    // Initialize I2C communication
    Wire.begin(0x04);
    Wire.onReceive(receiveEvent); // Register an event handler for I2C receive events

    // Start the system
    setupFedeer();
}

void loop() {
    // Enter the main loop
    mainLoop();
    //wait passively for RFID read from the Tiny1614
}

void receiveEvent(int howMany) {
    // Read the RFID tag sent from the Tiny1614
    String rfidTag = "";
    while (Wire.available()) {
        char c = Wire.read();
        rfidTag += c;
    }

    // Validate and process the RFID tag
    validateCatInfo(rfidTag);
}

void setupFedeer() {
    calibrateReservoir();
    loadFeedingSchedule();
    checkFeedingSchedule();
}

void calibrateReservoir() {
    // Code to calibrate the reservoir
    Serial.println("Calibrating reservoir...");
}

void initializeRTC() {
    // Code to initialize the RTC
    Serial.println("Initializing RTC...");
}

void loadFeedingSchedule() {
    // Code to load the feeding schedule
    Serial.println("Loading feeding schedule...");
}

void checkFeedingSchedule() {
    // Code to check the feeding schedule
    Serial.println("Checking feeding schedule...");
}

void checkIfAlreadyAte() {
    // Code to check if the cat has already eaten
    Serial.println("Checking if the cat has already eaten...");
    // need to add logic to load food if already ate before
    if (/* result of checkIfAlreadyAte() */) {
        loadFood();
    }
}

void validateCatInfo(String rfidTag) {
    // Code to validate cat's information
    Serial.println("Validating cat information...");
    Serial.println("RFID Tag: " + rfidTag);
    logCatEntry(rfidTag);
    openDoor();
}

void logCatEntry(String rfidTag) {
    // Code to log cat's entry
    Serial.println("Logging cat entry...");
}

void openDoor() {
    // Code to open the door
    Serial.println("Opening door...");
    Wire.beginTransmission(0x04); // Address of the Tiny1614
    Wire.write('O'); // Command to open the door
    Wire.endTransmission();
}

void determineFoodAmount() {
    // Code to determine the required amount of food
    Serial.println("Determining food amount...");
}

void rotateReservoir() {
    // Code to rotate the reservoir
    Serial.println("Rotating reservoir...");
}

void rotateFeedScrew() {
    // Code to rotate the feed screw
    Serial.println("Rotating feed screw...");
}

void loadFood() {
    // Code to handle the feeding process
    Serial.println("Feeding cat...");
    determineFoodAmount();
    rotateReservoir();
    rotateFeedScrew();
}

void mainLoop() {
    while (true) {
        // The ESP32 now waits passively for RFID data from the Tiny1614
        checkFeedingSchedule();
        // Add delay to avoid busy-waiting
        delay(1000);
    }
}
