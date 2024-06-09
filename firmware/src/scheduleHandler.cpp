#include <scheduleHandler.h>

// Generic function to check if the current time matches any of the given times
bool isItTime(const char* currentTime, const char* times[], size_t numTimes) {
    for (size_t i = 0; i < numTimes; ++i) {
        if (strncmp(times[i], currentTime, 5) == 0) {
            return true;
        }
    }
    return false;
}

void checkFeedingSchedule() {
    String data;
    JsonDocument doc;

    if (!readAndParseJson(data, doc)) {
        return;
    }

    char currentTime[6];
    if (!getCurrentTime(currentTime, sizeof(currentTime))) {
        return;
    }

    printAsciiBox("It is now: " + String(currentTime));

    for (JsonPair kv : doc.as<JsonObject>()) {
        const char* moduleName = kv.key().c_str();
        const JsonObject& module = kv.value().as<JsonObject>();

        const char* time1 = module["time1"];
        const char* time2 = module["time2"];
        bool active = module["active"];
        int amount_food = module["amount_food"];
        
        Serial.printf("Active: %s | Module: %s | Feed at: %s, %s | Amount: %d\n", active ? "Yes" : "No", moduleName, time1, time2, amount_food);

        const char* times[] = {time1, time2};
        if (active && isItTime(currentTime, times, 2)) {
            printAsciiBox("Feeding time for module: " + String(moduleName));
            Serial.print("Feeding amount: ");
            Serial.println(amount_food);

            int modulePosition = 0;
            if (strcmp(moduleName, "module1") == 0) {
                modulePosition = foodBay1;
            } else if (strcmp(moduleName, "module2") == 0) {
                modulePosition = foodBay2;
            } else if (strcmp(moduleName, "module3") == 0) {
                modulePosition = foodBay3;
            }
            moveAndFeed(modulePosition, amount_food);
        } else {
        }
    }
}
