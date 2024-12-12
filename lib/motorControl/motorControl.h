#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <LineSensor.h>

#define MOTOR_RIGHT_FORWARD 23
#define MOTOR_RIGHT_BACKWARD 22
#define MOTOR_LEFT_FORWARD 24
#define MOTOR_LEFT_BACKWARD 25
#define RIGHT_PWM 6
#define LEFT_PWM 7

int baseSpeed;

void controlMotors(int leftSpeed, int rightSpeed);
void stopMotors();
void turnLeft(int speed);
void turnRight(int speed);
void turnBack(int speed);
void moveForward(int speed);
void moveBackward(int speed);
void reverse(int speed);
void brake();
void rotate();
void attachInterrupts();
void detachInterrupts();
#endif