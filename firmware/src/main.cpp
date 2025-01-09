#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <FastAccelStepper.h>

// WiFi credentials
const char *ssid = "MPR18-2.4G";
const char *password = "missionconnected";

// MQTT broker details
const char *mqtt_server = "192.168.1.11";
const char *mqtt_user = "homeassistant";
const char *mqtt_password = "123456";
const char *mqtt_topic_move1 = "stepper/move1";
const char *mqtt_topic_move2 = "stepper/move2";
const char *mqtt_topic_endstop = "endstop/status";

// Stepper Motor 1
#define DIR_PIN_1 3
#define STEP_PIN_1 2
#define ENABLE_PIN_1 4

// Stepper Motor 2
#define DIR_PIN_2 6
#define STEP_PIN_2 5
#define ENABLE_PIN_2 7

// End Stop
#define END_STOP_PIN 42

WiFiClient espClient;
PubSubClient client(espClient);
FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper1 = NULL;
FastAccelStepper *stepper2 = NULL;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool endStopState = HIGH;
bool lastEndStopState = HIGH;
bool motorsRunning = false;

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
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  Serial.println(message);

  if (String(topic) == mqtt_topic_move1) {
    int command = message.toInt();
    if (command == 1) {
      motorsRunning = true;
      Serial.println("Motors started");
    } else if (command == 0) {
      motorsRunning = false;
      if (stepper1) {
        stepper1->stopMove();
      }
      if (stepper2) {
        stepper2->stopMove();
      }
      Serial.println("Motors stopped");
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic_move1);
      client.subscribe(mqtt_topic_move2);
      Serial.println("Subscribed to MQTT topics.");
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

  pinMode(END_STOP_PIN, INPUT_PULLUP); // Initialize end stop pin

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  engine.init();
  
  // Initialize Stepper 1
  stepper1 = engine.stepperConnectToPin(STEP_PIN_1);
  if (stepper1) {
    stepper1->setDirectionPin(DIR_PIN_1);
    stepper1->setEnablePin(ENABLE_PIN_1);
    stepper1->setAutoEnable(true);
    stepper1->setSpeedInHz(1000); // Set a default speed
    stepper1->setAcceleration(1000); // Set a default acceleration
    Serial.println("Stepper motor 1 initialized.");
  } else {
    Serial.println("Failed to initialize stepper motor 1.");
  }

  // Initialize Stepper 2
  stepper2 = engine.stepperConnectToPin(STEP_PIN_2);
  if (stepper2) {
    stepper2->setDirectionPin(DIR_PIN_2);
    stepper2->setEnablePin(ENABLE_PIN_2);
    stepper2->setAutoEnable(true);
    stepper2->setSpeedInHz(1000); // Set a default speed
    stepper2->setAcceleration(1000); // Set a default acceleration
    Serial.println("Stepper motor 2 initialized.");
  } else {
    Serial.println("Failed to initialize stepper motor 2.");
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Check end stop status
  int reading = digitalRead(END_STOP_PIN);
  if (reading != lastEndStopState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != endStopState) {
      endStopState = reading;
      if (endStopState == LOW) {
        Serial.println("End stop pressed.");
        client.publish(mqtt_topic_endstop, "1");
      } else {
        Serial.println("End stop released.");
        client.publish(mqtt_topic_endstop, "0");
      }
    }
  }
  lastEndStopState = reading;

  if (motorsRunning) {
    if (stepper1) {
      stepper1->move(100); // Move stepper1 continuously
    }
    if (stepper2) {
      stepper2->move(100); // Move stepper2 continuously
    }
  }
}