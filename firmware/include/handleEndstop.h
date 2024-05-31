// header file for handleEndstop.c
#ifndef HANDLEENDSTOP_H
#define HANDLEENDSTOP_H

#include <config.h>

// Function to handle endstop interrupt
void setupEndstopInterrupt(int pin);
bool checkEndstopHit();
bool checkEndstopReleased();
void updateEndstopState();

#endif