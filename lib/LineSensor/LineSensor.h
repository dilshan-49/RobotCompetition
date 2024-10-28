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
#define DR A14
#define DL A15

extern int sensor_array[NUM_SENSORS];
extern int readings[NUM_SENSORS+2];

void calibrate();
void readSensorVals();
int getError();
int detectJunc();
bool areAllBlack(int* array, int size);

#endif