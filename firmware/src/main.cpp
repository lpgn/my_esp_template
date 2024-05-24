#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>

// Replace with your network credentials
const char* ssid = "quarto_casal";
const char* password = "imgrumpy";
AsyncWebServer server(80);

// Function Prototypes
bool writeFile(String path, String data);
String readFile(String path);
void setupStorage();
void handleRoot(AsyncWebServerRequest *request);
void handleFileRequest(AsyncWebServerRequest *request);
void serveFile(AsyncWebServerRequest *request, String filePath);
void handleDataRequest(AsyncWebServerRequest *request);
void handleDataUpdate(AsyncWebServerRequest *request, JsonVariant &json);


void setup() {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi");

    setupStorage();
    AsyncCallbackJsonWebHandler* postDataHandler = new AsyncCallbackJsonWebHandler("/postdata", [](AsyncWebServerRequest *request, JsonVariant &json) {
        handleDataUpdate(request, json);
    });
    server.on("/", HTTP_GET, handleRoot);
    server.on("/data", HTTP_GET, handleDataRequest);
    server.addHandler(postDataHandler);
    server.onNotFound(handleFileRequest);
    server.begin();
}

void loop() {
    // No need to call server.handleClient() with AsyncWebServer
}

// Function to write data to a file
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

// Function to read data from a file
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

// Function to initialize LittleFS
void setupStorage()
{
    if (!LittleFS.begin(true))
    {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }
}

void handleRoot(AsyncWebServerRequest *request) {
    serveFile(request, "/index.html");
}

// Function to handle file requests
void handleFileRequest(AsyncWebServerRequest *request) {
    String filePath = request->url();
    serveFile(request, filePath);
}

// Function to serve a file
void serveFile(AsyncWebServerRequest *request, String filePath) {
    if (LittleFS.exists(filePath)) {
        File file = LittleFS.open(filePath, "r");
        request->send(file, filePath, "text/html");
        file.close();
    } else {
        request->send(404, "text/plain", "File not found");
    }
}

// Function to handle data requests
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