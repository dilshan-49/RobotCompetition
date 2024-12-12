#ifndef DOTTEDLINE_H
#define DOTTEDLINE_H

#include <Arduino.h>
#include <Wire.h>
#include <LineSensor.h>
#include <motorControl.h>

void following();
void PID_follow();

float Kp = 7;  
float Ki = 0.05; 
float Kd = 2.6;

int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];
int whiteThreshold[NUM_SENSORS];

#endif // DOTTEDLINE_H