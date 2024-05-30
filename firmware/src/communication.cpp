#include "communication.h" 

// Function to receive RFID tag data from Tiny1614
void receiveEvent(int howMany) {
    // Read the RFID tag data from Tiny1614
    String rfidTag = "";
    while (Wire.available()) {
        char c = Wire.read();
        rfidTag += c;
    }
    // Validate and process the RFID tag data
    validateCatInfo(rfidTag);
}

// Function to transmit order to open the door
void transmitOpenDoor() {
    // Code to open the door
    Serial.println("Opening door...");
    Wire.beginTransmission(0x04); // Address of the Tiny1614
    Wire.write('O'); // Command to open the door
    Wire.endTransmission();
}


void printAsciiBox(const String& message) {
    int length = message.length();
    String border = "";
    for (int i = 0; i < length + 4; ++i) {
        border += '*';
    }
    Serial.println(border);
    Serial.println("* " + message + " *");
    Serial.println(border);
}
