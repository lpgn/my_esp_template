#include <Config.h>

void checkFeedingSchedule() {
    Serial.println("Checking feeding schedule...");

    String data = readFile("/data.json");
    if (data.isEmpty()) {
        Serial.println("Failed to read data.json");
        return;
    }

    Serial.println("Successfully read data.json");

    JsonDocument doc; // Adjust the size as needed
    DeserializationError error = deserializeJson(doc, data);
    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    Serial.println("Successfully parsed JSON");

    // Get the current time from RTC
    RtcDateTime now = Rtc.GetDateTime();
    if (!now.IsValid()) {
        Serial.println("Failed to retrieve valid time from RTC.");
        return;
    }
    char currentTime[6];
    snprintf(currentTime, sizeof(currentTime), "%02d:%02d", now.Hour(), now.Minute());

    Serial.print("Current time: ");
    Serial.println(currentTime);

    for (JsonPair module : doc.as<JsonObject>()) {
        const char* time1 = module.value()["time1"];
        const char* time2 = module.value()["time2"];
        bool active = module.value()["active"];
        int amount_food = module.value()["amount_food"];

        Serial.print("Checking module: ");
        Serial.println(module.key().c_str());
        Serial.print("Time 1: ");
        Serial.println(time1);
        Serial.print("Time 2: ");
        Serial.println(time2);
        Serial.print("Active: ");
        Serial.println(active ? "true" : "false");
        Serial.print("Amount of food: ");
        Serial.println(amount_food);

        if (active && (strncmp(time1, currentTime, 5) == 0 || strncmp(time2, currentTime, 5) == 0)) {
            Serial.print("Feeding time for module: ");
            Serial.println(module.key().c_str());
            // Placeholder for feeding code
            // moveReservoir();
            // moveScrew(amount_food);
        }
    }

    Serial.println("Finished checking feeding schedule");
}
