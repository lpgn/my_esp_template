#include <Arduino.h>
#include <FastAccelStepper.h>

// Stepper Motor
#define DIR_PIN 8
#define STEP_PIN 3
#define ENABLE_PIN 46

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper = NULL;

void setup() {
  Serial.begin(115200); // Initialize serial monitor with fast speed
  Serial.println("Serial monitor started.");

  engine.init();
  stepper = engine.stepperConnectToPin(STEP_PIN);
  if (stepper) {
    stepper->setDirectionPin(DIR_PIN);
    stepper->setEnablePin(ENABLE_PIN);
    stepper->setAutoEnable(true);
    stepper->setSpeedInHz(1000); // Set a default speed
    stepper->setAcceleration(1000); // Set a default acceleration
    Serial.println("Stepper motor initialized.");
  } else {
    Serial.println("Failed to initialize stepper motor.");
  }
}

void loop() {
  if (stepper) {
    Serial.println("Moving stepper motor to the right...");
    stepper->move(2000); // Move 200 steps to the right
    while (stepper->isRunning()) {
      // Waiting for the stepper to finish the move
    }
    Serial.println("Stepper movement to the right complete.");

    delay(1000); // Wait for 1 second

    Serial.println("Moving stepper motor to the left...");
    stepper->move(-2000); // Move 200 steps to the left
    while (stepper->isRunning()) {
      // Waiting for the stepper to finish the move
    }
    Serial.println("Stepper movement to the left complete.");

    delay(1000); // Wait for 1 second

    // Disable the stepper motor
    stepper->disableOutputs();
    Serial.println("Stepper motor disabled.");

    delay(5000); // Pause for 5 seconds

    // Enable the stepper motor
    stepper->enableOutputs();
    Serial.println("Stepper motor enabled.");
  }
}