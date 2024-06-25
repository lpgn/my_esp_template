#include "communication.h" 

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
