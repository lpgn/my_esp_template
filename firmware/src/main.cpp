#include <Arduino.h>
#include <AccelStepper.h>

#define DIR_PIN  17  // Set your direction pin here
#define STEP_PIN 16  // Set your step pin here
#define EN_PIN   18  // Set your enable pin here
#define DIR_PIN2  8  // Set your direction pin here
#define STEP_PIN2 3  // Set your step pin here
#define EN_PIN2   46  // Set your enable pin here

const int stepsPerRevolution = 1600; // Adjust this according to your stepper motor
AccelStepper stepper1(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);
AccelStepper stepper2(AccelStepper::DRIVER, STEP_PIN2, DIR_PIN2);

void setup() {
  Serial.begin(115200);

  // Initialize the enable pins
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, LOW); // Enable the stepper driver 1
  pinMode(EN_PIN2, OUTPUT);
  digitalWrite(EN_PIN2, LOW); // Enable the stepper driver 2

  // Set max speed and acceleration for both steppers
  stepper1.setMaxSpeed(5000); // Set speed to 5000 steps per second for stepper 1
  stepper1.setAcceleration(2000); // Set acceleration to 2000 steps per second^2 for stepper 1
  stepper2.setMaxSpeed(5000); // Set speed to 5000 steps per second for stepper 2
  stepper2.setAcceleration(2000); // Set acceleration to 2000 steps per second^2 for stepper 2
}

void loop() {
  // Move stepper1 forward 3 revolutions
  stepper1.moveTo(stepsPerRevolution * 3);
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
  }
  delay(3000); // Wait for 3 seconds

  // Move stepper1 backward 3 revolutions
  stepper1.moveTo(-stepsPerRevolution * 3);
  while (stepper1.distanceToGo() != 0) {
    stepper1.run();
  }
  delay(3000); // Wait for 3 seconds

  // Move stepper2 forward 3 revolutions
  stepper2.moveTo(stepsPerRevolution * 3);
  while (stepper2.distanceToGo() != 0) {
    stepper2.run();
  }
  delay(3000); // Wait for 3 seconds

  // Move stepper2 backward 3 revolutions
  stepper2.moveTo(-stepsPerRevolution * 3);
  while (stepper2.distanceToGo() != 0) {
    stepper2.run();
  }
  delay(3000); // Wait for 3 seconds
}
