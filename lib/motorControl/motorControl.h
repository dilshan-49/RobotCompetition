#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <LineSensor.h>

#define MOTOR_RIGHT_FORWARD 23
#define MOTOR_RIGHT_BACKWARD 22
#define MOTOR_LEFT_FORWARD 24
#define MOTOR_LEFT_BACKWARD 25
#define RIGHT_PWM 12
#define LEFT_PWM 13

extern int baseSpeed;

void controlMotors(int leftSpeed, int rightSpeed);
void stopMotors();
void turnLeft(int rspeed, int lspeed);
void turnRight(int lspeed, int rspeed);
void turnBack(int speed);
void moveForward(int speed);
void moveBackward(int speed);
void reverse(int speed);
void brake();
void rotate();
#endif