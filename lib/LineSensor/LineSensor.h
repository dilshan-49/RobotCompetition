#ifndef LINESENSOR_H
#define LINESENSOR_H

#include <Arduino.h>

#define NUM_SENSORS 8
#define D1 A0
#define D2 A1
#define D3 A2
#define D4 A3
#define D5 A4
#define D6 A5
#define D7 A6
#define D8 A7
#define DR A8
#define DL A9

extern int sensor_array[NUM_SENSORS];
extern int threshold[NUM_SENSORS];
extern int weights[NUM_SENSORS+2];
int readings[NUM_SENSORS+2];

extern int thresholdR;
extern int thresholdL;

bool black = false;

void calibrate();
void readSensorVals();
int getError();
int detectJunc();

#endif