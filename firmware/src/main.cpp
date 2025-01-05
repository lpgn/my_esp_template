#include <Arduino.h>
#include <FastAccelStepper.h>

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

FastAccelStepperEngine engine = FastAccelStepperEngine();
FastAccelStepper *stepper1 = NULL;
FastAccelStepper *stepper2 = NULL;

void setup() {
  Serial.begin(115200); // Initialize serial monitor with fast speed
  Serial.println("Serial monitor started.");

  pinMode(END_STOP_PIN, INPUT_PULLUP); // Initialize end stop pin

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