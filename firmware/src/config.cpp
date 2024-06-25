#include "config.h"

ESP32Time rtc;

RtcDS3231<TwoWire> Rtc(Wire);
int sdaPin = 4;
int sclPin = 5;

WiFiMulti wifiMulti;
const char *wifi_network_hostname = "name_hostname";
const char *soft_ap_ssid = "name_SSID";
const char *soft_ap_password = "name_password";

AsyncWebServer server(80);

JsonDocument doc;

unsigned long lastCallTime = 0;
unsigned long lastCalibrationTime = 0;