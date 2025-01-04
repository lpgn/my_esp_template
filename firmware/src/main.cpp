#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <FastAccelStepper.h>

// WiFi credentials
const char *ssid = "raccacoonie";
const char *password = "newgerryforever2018";

// MQTT broker details
const char *mqtt_server = "192.168.1.11";
const char *mqtt_user = "homeassistant";
const char *mqtt_password = "123456";
const char *mqtt_topic = "stepper/move";

// Stepper Motor
#define DIR_PIN 8
#define STEP_PIN 3
#define ENABLE_PIN 46

WiFiClient espClient;
PubSubClient client(espClient);
FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (unsigned int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Convert payload to integer
  int steps = atoi((char*)payload);

  // Move the stepper motor
  if (stepper) {
    Serial.print("Moving stepper motor by ");
    Serial.print(steps);
    Serial.println(" steps...");
    stepper->move(steps);
    while (stepper->isRunning()) {
      // Waiting for the stepper to finish the move
    }
    Serial.println("Stepper movement complete.");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic);
      Serial.println("Subscribed to MQTT topic.");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200); // Initialize serial monitor with fast speed
  Serial.println("Serial monitor started.");

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  engine.init();
  stepper = engine.stepperConnectToPin(STEP_PIN);
  if (stepper) {
    stepper->setDirectionPin(DIR_PIN);
    stepper->setEnablePin(ENABLE_PIN);
    stepper->setAutoEnable(true);
    Serial.println("Stepper motor initialized.");
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}