#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "config.h"


void receiveEvent(int howMany); // Receives RFID tag data from Tiny1614
void printAsciiBox(const String& message);
void transmitOpenDoor(); // Opens the door



#endif // COMMUNICATION_H
