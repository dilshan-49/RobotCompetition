#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <LineSensor.h>
#include <pinDefinitions.h>

extern int baseSpeed;
extern int turnSpeed;
extern volatile int encL;
extern volatile int encR;
extern float KpEn;
extern float KiEn;
extern float KdEn;

void controlMotors(int leftSpeed, int rightSpeed);
void stopMotors();
void turnLeft();
void turnRight();
void turnBack(bool side); // true for right, false for left
void moveForward();
void moveBackward();
void reverse(int speed);
void brake();
void rotate();
void attachInterrupts();
void detachInterrupts();

#endif