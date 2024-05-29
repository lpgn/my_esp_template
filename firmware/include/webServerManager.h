#ifndef WEB_SERVER_MANAGER_H
#define WEB_SERVER_MANAGER_H
#include "config.h"

void serverHandle();
void handleRoot(AsyncWebServerRequest *request);
void handleFileRequest(AsyncWebServerRequest *request);
void serveFile(AsyncWebServerRequest *request, String filePath);
void handleDataRequest(AsyncWebServerRequest *request);
void handleDataUpdate(AsyncWebServerRequest *request, JsonVariant &json);

//

#endif // WEB_SERVER_MANAGER_H