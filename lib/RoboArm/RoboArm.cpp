#include <RoboArm.h>
#include <Servo.h>
#include <Arduino.h>

Servo myServo;
void armInitializing()
{
  myServo.attach(3);
  myServo.write(0);
  delay(1000);
}

void grabBox()
{
  for (int i = 0; i < 100; i = i + 5)
  {
    myServo.write(i);
    delay(50);
  }
  // Move servo to 0 degrees to grab
  delay(500); // Allow time for the servo to reach the position
}

void releaseBox()
{
  myServo.write(0); // Move servo to 180 degrees to release
  delay(500);       // Allow time for the servo to reach the position
}

void halfOpen()
{
  for (int i = 0; i < 60; i = i + 5)
  {
    myServo.write(i);
    delay(50);
  }
}