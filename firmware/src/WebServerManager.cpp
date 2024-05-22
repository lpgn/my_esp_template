#include "WebServerManager.h"

// HTTP status codes
const int HTTP_OK = 200;
const int HTTP_INTERNAL_SERVER_ERROR = 500;
const int HTTP_METHOD_NOT_ALLOWED = 405;

void serverHandle()
{
    // Inicializa o sistema de arquivos
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    // Servir index.html
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", String(), false);
    });

    // Servir qualquer arquivo diretamente do sistema de arquivos (por exemplo, style.css, script.js)
    server.on("^(\\/([a-zA-Z0-9_\\.-]+)*)$", HTTP_GET, [](AsyncWebServerRequest *request) {
        String file = request->pathArg(0);
        Serial.printf("Serving file %s\n", file.c_str());
        request->send(LittleFS, file, String(), false);
    });

    // Endpoint para atualizar dados JSON
    server.on("/postdata", HTTP_POST, [](AsyncWebServerRequest *request) {
        if (request->hasParam("plain", true)) {
            String data = request->getParam("plain", true)->value();
            File file = LittleFS.open("/data.json", "w");
            if (!file) {
                request->send(HTTP_INTERNAL_SERVER_ERROR, "application/json", "{\"status\":\"fail\"}");
                return;
            }
            file.print(data);
            file.close();
            request->send(HTTP_OK, "application/json", "{\"status\":\"success\"}");
        } else {
            request->send(HTTP_METHOD_NOT_ALLOWED, "application/json", "{\"status\":\"fail\"}");
        }
    });

    // Endpoint para obter dados JSON
    server.on("/getdata", HTTP_GET, [](AsyncWebServerRequest *request) {
        File file = LittleFS.open("/data.json", "r");
        if (!file) {
            request->send(HTTP_INTERNAL_SERVER_ERROR, "application/json", "{\"status\":\"fail\"}");
            return;
        }
        String json = file.readString();
        file.close();
        request->send(HTTP_OK, "application/json", json);
    });

    // Outros endpoints existentes
    server.on("/moveStepper", HTTP_POST, handleMoveStepper);
    server.on("/setAcceleration", HTTP_POST, handleSetAcceleration);
    server.on("/setSpeed", HTTP_POST, handleSetSpeed);

    // Handler para 404 Not Found
    server.onNotFound([](AsyncWebServerRequest *request) {
        request->send(404, "text/plain", "404: Not Found");
    });
}

// // Funções de controle do stepper motor
// void handleMoveStepper(AsyncWebServerRequest *request) {
//     if (request->method() == HTTP_POST) {
//         if (request->hasParam("plain", true)) {
//             int steps = request->getParam("plain", true)->value().toInt();
//             Serial.printf("Moving stepper by %d steps\n", steps);
//             moveStepper(steps, stepperReservoir);
//             request->send(HTTP_OK, "text/plain", "Stepper moved");
//         } else {
//             request->send(HTTP_METHOD_NOT_ALLOWED, "text/plain", "Method Not Allowed");
//         }
//     }
// }

// void handleSetAcceleration(AsyncWebServerRequest *request) {
//     if (request->method() == HTTP_POST) {
//         if (request->hasParam("plain", true)) {
//             int acceleration = request->getParam("plain", true)->value().toInt();
//             Serial.printf("Setting acceleration to %d\n", acceleration);
//             setAcceleration(acceleration, stepperReservoir);
//             request->send(HTTP_OK, "text/plain", "Acceleration set");
//         } else {
//             request->send(HTTP_METHOD_NOT_ALLOWED, "text/plain", "Method Not Allowed");
//         }
//     }
// }

// void handleSetSpeed(AsyncWebServerRequest *request) {
//     if (request->method() == HTTP_POST) {
//         if (request->hasParam("plain", true)) {
//             int speed = request->getParam("plain", true)->value().toInt();
//             Serial.printf("Setting speed to %d\n", speed);
//             setSpeed(speed, stepperReservoir);
//             request->send(HTTP_OK, "text/plain", "Speed set");
//         } else {
//             request->send(HTTP_METHOD_NOT_ALLOWED, "text/plain", "Method Not Allowed");
//         }
//     }
// }

// // Implementação das funções de leitura e escrita (se necessário)
// bool writeFile(String path, String data) {
//     File file = LittleFS.open(path, "w");
//     if (!file) {
//         return false;
//     }
//     file.print(data);
//     file.close();
//     return true;
// }

// String readFile(String path) {
//     File file = LittleFS.open(path, "r");
//     if (!file) {
//         return "";
//     }
//     String data = file.readString();
//     file.close();
//     return data;
// }
