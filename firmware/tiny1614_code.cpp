
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>

// Pin definitions for the RFID reader
#define RST_PIN 9
#define SS_PIN 10

MFRC522 rfid(SS_PIN, RST_PIN);

// Function declarations
void receiveEvent(int howMany);
void requestEvent();
void openDoor();
void readRFID();
String getRFIDTag();

// Variables
String currentRFIDTag = "";

// Function definitions

void setup() {
    // Initialize I2C communication
    Wire.begin(0x04); // Address of this device
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);

    // Initialize SPI bus
    SPI.begin();
    
    // Initialize RFID reader
    rfid.PCD_Init();

    // Initialize servo motor pin
    pinMode(RST_PIN, OUTPUT);
}

void loop() {
    // Read RFID tag periodically
    readRFID();
    delay(100);
}

void receiveEvent(int howMany) {
    while (Wire.available()) {
        char c = Wire.read();
        if (c == 'O') {
            openDoor();
        }
    }
}

void requestEvent() {
    Wire.write(currentRFIDTag.c_str());
}

void openDoor() {
    // Code to open the door
    digitalWrite(RST_PIN, HIGH); // Example to activate servo motor
    delay(1000); // Keep the door open for 1 second
    digitalWrite(RST_PIN, LOW); // Close the door
}

void readRFID() {
    if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
        currentRFIDTag = "";
        return;
    }
    currentRFIDTag = getRFIDTag();
    rfid.PICC_HaltA();

    // Send RFID tag to ESP32
    Wire.beginTransmission(0x04);
    Wire.write(currentRFIDTag.c_str());
    Wire.endTransmission();
}

String getRFIDTag() {
    String tag = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
        tag += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        tag += String(rfid.uid.uidByte[i], HEX);
    }
    tag.toUpperCase();
    return tag;
}
