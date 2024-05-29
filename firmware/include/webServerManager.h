#ifndef WEB_SERVER_MANAGER_H
#define WEB_SERVER_MANAGER_H
#include "config.h"

void serverHandle();
// void handlePostData(AsyncWebServerRequest *request);
// void handleGetData(AsyncWebServerRequest *request);
// void handleMoveStepper(AsyncWebServerRequest *request);
// void handleSetAcceleration(AsyncWebServerRequest *request);
// void handleSetSpeed(AsyncWebServerRequest *request);

void handleRoot(AsyncWebServerRequest *request);
void handleFileRequest(AsyncWebServerRequest *request);
void serveFile(AsyncWebServerRequest *request, String filePath);
void handleDataRequest(AsyncWebServerRequest *request);
void handleDataUpdate(AsyncWebServerRequest *request, JsonVariant &json);

//

#endif // WEB_SERVER_MANAGER_H