#include "feedingMechanism.h"

void moveAndFeed(int modulePosition, int amount_food) {
    Serial.println("Starting feeding process...");
    Serial.printf("Moving reservoir to position %d\n", modulePosition);
    moveReservoir(modulePosition);
    printAsciiBox("Reservoir moved to position " + String(modulePosition));
    Serial.printf("Dispensing %d grams of food\n", amount_food);
    moveScrew(amount_food * stepsPerGram);
    printAsciiBox(String(amount_food) + " grams of food dispensed");
    Serial.println("Feeding process completed.");
}

