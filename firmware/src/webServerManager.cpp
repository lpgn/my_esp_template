#include "webServerManager.h"



void serverHandle()
{
    // Additional routes
    AsyncCallbackJsonWebHandler* postDataHandler = new AsyncCallbackJsonWebHandler("/postdata", [](AsyncWebServerRequest *request, JsonVariant &json) {
        handleDataUpdate(request, json);
    });
    server.on("/", HTTP_GET, handleRoot);
    server.on("/data", HTTP_GET, handleDataRequest);
    // Serving any file directly from the filesystem (e.g., style.css, script.js)
    server.on("^(\\/[a-zA-Z0-9_.-]*)$", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    String file = request->pathArg(0);

    Serial.printf("Serving file %s\n\r", file.c_str());
    request->send(LittleFS, file, String(), false); });
    server.addHandler(postDataHandler);
    server.onNotFound(handleFileRequest);
    server.begin();
}

// Handle requests to the root URL
void handleRoot(AsyncWebServerRequest *request) {
    serveFile(request, "/index.html");
}

// Handle requests for files
void handleFileRequest(AsyncWebServerRequest *request) {
    String filePath = request->url();
    serveFile(request, filePath);
}

// Serve a file from LittleFS
void serveFile(AsyncWebServerRequest *request, String filePath) {
    if (LittleFS.exists(filePath)) {
        File file = LittleFS.open(filePath, "r");
        request->send(file, filePath, "text/html");
        file.close();
    } else {
        request->send(404, "text/plain", "File not found");
    }
}

// Handle data requests
void handleDataRequest(AsyncWebServerRequest *request) {
    String data = readFile("/data.json");
    if (data.isEmpty()) {
        request->send(500, "text/plain", "Failed to read data.json");
        return;
    }
    request->send(200, "application/json", data);
}
// Function to handle POST /postdata
void handleDataUpdate(AsyncWebServerRequest *request, JsonVariant &json)
{
    JsonObject obj = json.as<JsonObject>();

    if (obj.containsKey("module") && obj.containsKey("key") && obj.containsKey("value"))
    {
        const char* module = obj["module"];
        const char* key = obj["key"];
        auto value = obj["value"];

        String data = readFile("/data.json");
        if (data.isEmpty())
        {
            request->send(500, "text/plain", "Failed to read data.json");
            return;
        }

        JsonDocument jsonData;
        deserializeJson(jsonData, data);
        JsonObject jsonObj = jsonData[module];

        if (strcmp(key, "cat_name") == 0 || strcmp(key, "amount_food") == 0 || strcmp(key, "time1") == 0 || strcmp(key, "time2") == 0)
        {
            jsonObj[key] = value.as<const char*>();
        }
        else if (strcmp(key, "active") == 0)
        {
            jsonObj[key] = value.as<bool>();
        }

        String updatedData;
        serializeJson(jsonData, updatedData);

        if (!writeFile("/data.json", updatedData))
        {
            request->send(500, "text/plain", "Failed to write data.json");
            return;
        }

        request->send(200, "text/plain", "Data updated successfully");
    }
    else
    {
        request->send(400, "text/plain", "Invalid request");
    }
}