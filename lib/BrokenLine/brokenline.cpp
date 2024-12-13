#include <Wire.h>
#include <Arduino.h>
#include <motorControl.h>
#include <LineSensor.h>



#define IRS A0

void setup() {
  pinMode(IRS, INPUT);
  Serial.begin(9600);
}

void loop() {
  int IRV = analogRead(IRS);

  // Threshold 
  if (IRV > 500) { 
    moveForward(baseSpeed);
  } else { 
    idle();
  }
}


void idle() {
  Serial.println("Searching Line");
  // Briefly move forward to reconnect with the line
  moveForward(baseSpeed);
  delay(200); // Adjust based on dash size
  stopMotors();
}

