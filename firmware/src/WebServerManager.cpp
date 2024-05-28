#include "WebServerManager.h"

void serverHandle()
{
    // Serving index.html
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(LittleFS, "/index.html", String(), false); });
    
    // Serving any file directly from the filesystem (e.g., style.css, script.js)
    server.on("^(\\/[a-zA-Z0-9_.-]*)$", HTTP_GET, [](AsyncWebServerRequest *request)
              {
        String file = request->pathArg(0);
        Serial.printf("Serving file %s\n\r", file.c_str());
        request->send(LittleFS, file, String(), false); });

    // 404 Not Found Handler
    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "404: Not Found");
    });
    //
    server.on("/moveStepper", HTTP_POST, handleMoveStepper);
    server.on("/setAcceleration", HTTP_POST, handleSetAcceleration);
    server.on("/setSpeed", HTTP_POST, handleSetSpeed);

    // Additional routes
    AsyncCallbackJsonWebHandler* postDataHandler = new AsyncCallbackJsonWebHandler("/postdata", [](AsyncWebServerRequest *request, JsonVariant &json) {
        handleDataUpdate(request, json);
    });
    server.on("/", HTTP_GET, handleRoot);
    server.on("/data", HTTP_GET, handleDataRequest);
    server.addHandler(postDataHandler);
    server.onNotFound(handleFileRequest);
    server.begin();
}

// Handle requests to the root URL
void handleRoot(AsyncWebServerRequest *request)
{
    request->send(200, "text/plain", "Hello, world");
}

// Handle requests for files
void handleFileRequest(AsyncWebServerRequest *request)
{
    serveFile(request, request->url());
}

// Serve a file from LittleFS
void serveFile(AsyncWebServerRequest *request, String filePath)
{
    File file = LittleFS.open(filePath, "r");
    if (!file)
    {
        request->send(404, "text/plain", "File not found");
        return;
    }
    String contentType = "text/plain";
    if (filePath.endsWith(".html"))
    {
        contentType = "text/html";
    }
    request->send(file, filePath, contentType);
    file.close();
}

// Handle data requests
void handleDataRequest(AsyncWebServerRequest *request)
{
    String data = readFile("/data.json");
    if (data.isEmpty())
    {
        request->send(500, "text/plain", "Failed to read data.json");
        return;
    }
    request->send(200, "application/json", data);
}

// Handle data updates
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
