#include <Wire.h>
#include <Arduino.h>
#include <motorControl.h>
#include <LineSensor.h>

#include <Ultrasonic.h>




// Define pins
#define TRIG_PIN 9
#define ECHO_PIN 10
#define IR_SENSOR A0

// Thresholds
const int gateOpenThreshold = 20; // Distance in cm for gate open detection

// Ultrasonic setup
Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(IR_SENSOR, INPUT);
}

void loop() {
  // Measure distance to the gate
  long distance = ultrasonic.read();

  if (distance > gateOpenThreshold) { // Gate is open
    Serial.println("Gate is Open");
    moveForward(baseSpeed);
    delay(1000);              // Pause in the black box
    startBlackLineFollowing(); // Start black line following
  } else { // Gate is closed
    Serial.println("Gate is Closed");
    stopMotors();
    delay(100); // Wait a moment before checking again
  }
}



void startBlackLineFollowing() {
  Serial.println("Starting Black Line Following");

  // Black line following logic
  while (true) { // Infinite loop for continuous line-following
    int sensorValue = analogRead(IR_SENSOR);

    if (sensorValue < 500) { // Black line detected
      moveForward(baseSpeed);
    } else { // White space detected
      stopMotors();
    }
  }
}

