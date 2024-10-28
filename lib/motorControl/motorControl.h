#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

#include <Arduino.h>
#include <LineSensor.h>

#define MOTOR_RIGHT_FORWARD 22
#define MOTOR_RIGHT_BACKWARD 23
#define MOTOR_LEFT_FORWARD 25
#define MOTOR_LEFT_BACKWARD 24
#define RIGHT_PWM 6
#define LEFT_PWM 7

extern int baseSpeed;

void controlMotors(int leftSpeed, int rightSpeed);
void stopMotors();
void turnLeft(int rspeed,int lspeed);
void turnRight(int lspeed,int rspeed);
void turnBack(int speed);
void moveForward(int speed);
void reverse(int speed);
void brake();

#endif 