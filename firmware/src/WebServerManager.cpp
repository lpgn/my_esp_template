#include "WebServerManager.h"
#include "Config.h"

// HTTP status codes
const int HTTP_OK = 200;
const int HTTP_INTERNAL_SERVER_ERROR = 500;
const int HTTP_METHOD_NOT_ALLOWED = 405;

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
    server.on("/moveStepper", HTTP_POST, handleMoveStepper);
    server.on("/setAcceleration", HTTP_POST, handleSetAcceleration);
    server.on("/setStepsPerMM", HTTP_POST, handleSetStepsPerMM);
    server.on("/toggleStepper", HTTP_POST, handleToggleStepper); // Add this line
}

