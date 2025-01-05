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
const char *mqtt_topic_move1 = "stepper/move1";
const char *mqtt_topic_status = "stepper/status";

// Stepper Motor 1
#define DIR_PIN_1 8
#define STEP_PIN_1 3
#define ENABLE_PIN_1 46

// Stepper Motor 2
#define DIR_PIN_2 17
#define STEP_PIN_2 16
#define ENABLE_PIN_2 18

// End Stop
#define END_STOP_PIN 42

WiFiClient espClient;
PubSubClient client(espClient);
FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper1 = NULL;
FastAccelStepper *stepper2 = NULL;

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

  if (strcmp(topic, mqtt_topic_move1) == 0) {
    // Convert payload to integer
    int command = atoi((char*)payload);
    Serial.print("Command received: ");
    Serial.println(command);

    if (command == 1) {
      // Move stepper 1
      if (stepper1) {
        Serial.println("Moving stepper motor 1...");
        stepper1->move(10000); // Move a large number of steps to ensure it reaches the end stop
        while (stepper1->isRunning()) {
          if (digitalRead(END_STOP_PIN) == LOW) {
            stepper1->forceStop(); // Stop the motor if the end stop is pressed
            Serial.println("End stop pressed. Stepper motor 1 stopped.");
            client.publish(mqtt_topic_status, "Stepper motor 1 stopped due to end stop.");
            break;
          }
        }
        Serial.println("Stepper motor 1 movement complete.");
      } else {
        Serial.println("Stepper motor 1 not initialized.");
      }
    }
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32Client", mqtt_user, mqtt_password)) {
      Serial.println("connected");
      client.subscribe(mqtt_topic_move1);
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

  if (stepper1 && stepper2) {
    Serial.println("Moving stepper motors to the right...");
    stepper1->move(200); // Move 200 steps to the right
    stepper2->move(200); // Move 200 steps to the right
    while (stepper1->isRunning() || stepper2->isRunning()) {
      // Waiting for the steppers to finish the move
    }
    Serial.println("Stepper motors movement to the right complete.");

    delay(1000); // Wait for 1 second

    Serial.println("Moving stepper motors to the left...");
    stepper1->move(-200); // Move 200 steps to the left
    stepper2->move(-200); // Move 200 steps to the left
    while (stepper1->isRunning() || stepper2->isRunning()) {
      // Waiting for the steppers to finish the move
    }
    Serial.println("Stepper motors movement to the left complete.");

    delay(1000); // Wait for 1 second

    // Move stepper 2 until the end stop is pressed
    Serial.println("Moving stepper motor 2 until end stop is pressed...");
    stepper2->move(10000); // Move a large number of steps to ensure it reaches the end stop
    while (stepper2->isRunning()) {
      if (digitalRead(END_STOP_PIN) == LOW) {
        stepper2->forceStop(); // Stop the motor if the end stop is pressed
        Serial.println("End stop pressed. Stepper motor 2 stopped.");
        break;
      }
    }

    // Disable the stepper motors
    stepper1->disableOutputs();
    stepper2->disableOutputs();
    Serial.println("Stepper motors disabled.");

    delay(5000); // Pause for 5 seconds

    // Enable the stepper motors
    stepper1->enableOutputs();
    stepper2->enableOutputs();
    Serial.println("Stepper motors enabled.");
  }
}