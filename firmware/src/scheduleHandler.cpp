#include <Config.h>

void checkFeedingSchedule() {
    Serial.println("Checking feeding schedule...");

    String data = readFile("/data.json");
    if (data.isEmpty()) {
        Serial.println("Failed to read data.json");
        return;
    }

    JsonDocument doc;
    DeserializationError error = deserializeJson(doc, data);
    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return;
    }

    // Get the current time from RTC
    RtcDateTime now = Rtc.GetDateTime();
    char currentTime[6];
    snprintf(currentTime, sizeof(currentTime), "%02d:%02d", now.Hour(), now.Minute());

    for (JsonPair module : doc.as<JsonObject>()) {
      const char* time1 = module.value()["time1"];
      const char* time2 = module.value()["time2"];
      bool active = module.value()["active"];
      int amount_food = module.value()["amount_food"];

      if (active && (strcmp(time1, currentTime) == 0 || strcmp(time2, currentTime) == 0)) {
        // It's time to feed the cat
        Serial.print("Feeding time for module: ");
        Serial.println(module.key().c_str());
        moveReservoir();
        moveScrew(amount_food);
      }
    }
}