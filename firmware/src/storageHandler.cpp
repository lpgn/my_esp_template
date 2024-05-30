#include "storageHandler.h"

bool writeFile(String path, String data)
{
    File file = LittleFS.open(path, "w");
    if (!file)
    {
        Serial.printf("Failed to open file '%s' for writing\n", path.c_str());
        return false;
    }
    int bytesWritten = file.print(data);
    file.close();
    Serial.printf("Written to file '%s' (%d bytes)\n", path.c_str(), bytesWritten);
    return true;
}

String readFile(String path)
{
    if (!LittleFS.exists(path))
    {
        Serial.printf("File '%s' does not exist\n", path.c_str());
        return "";
    }
    File file = LittleFS.open(path, "r");
    String data = file.readString();
    file.close();
    return data;
}

void setupStorage()
{
    if (!LittleFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
}

bool writeDataJson()
{
    Serial.println("JSON serialize - BEGIN");
    String jsonString;
    serializeJson(doc, jsonString);
    Serial.println("JSON serialize - COMPLETE");
    return writeFile("/data.json", jsonString);
}

void readDataJson()
{
    Serial.println("Starting to look for JSON file");
    String json = LittleFS.exists("/data.json") ? readFile("/data.json") : readFile("/sample.json");
    Serial.println("JSON deserialize - BEGIN");
    deserializeJson(doc, json);
    Serial.println("JSON deserialize - COMPLETE");
}

bool readAndParseJson(String& data, JsonDocument& doc) {
    data = readFile("/data.json");
    if (data.isEmpty()) {
        Serial.println("Failed to read data.json");
        return false;
    }

    DeserializationError error = deserializeJson(doc, data);
    if (error) {
        Serial.print("Failed to parse JSON: ");
        Serial.println(error.c_str());
        return false;
    }

    return true;
}