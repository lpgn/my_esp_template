#include <Arduino.h>
#include <AccelStepper.h>

#define DIR_PIN  33  // Set your direction pin here
#define STEP_PIN 32  // Set your step pin here
#define EN_PIN   27  // Set your enable pin here

const int stepsPerRevolution = 1600; // Adjust this according to your stepper motor
AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

void setup() {
  Serial.begin(115200);

  // Initialize the enable pin
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // Enable the stepper driver

  // Set max speed and acceleration
  stepper.setMaxSpeed(12000); // Set speed to 1000 steps per second
  stepper.setAcceleration(12000); // Set acceleration to 1000 steps per second^2
}

void loop() {
  // Move forward 3 revolutions
  stepper.moveTo(stepsPerRevolution * 3);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(3000); // Wait for 3 seconds

  // Move backward 3 revolutions
  stepper.moveTo(-stepsPerRevolution * 3);
  while (stepper.distanceToGo() != 0) {
    stepper.run();
  }
  delay(3000); // Wait for 3 seconds
}
