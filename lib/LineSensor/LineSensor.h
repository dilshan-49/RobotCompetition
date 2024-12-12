#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>

#define NUM_SENSORS 10
#define D1 A9
#define D2 A8
#define D3 A7
#define D4 A6
#define D5 A5
#define D6 A4
#define D7 A3
#define D8 A2
#define D9 A1
#define D10 A0

extern int sensor_array[NUM_SENSORS];
extern int readings[NUM_SENSORS];
extern int threshold[NUM_SENSORS];
extern const bool white;
extern const bool black;

void readSensorVals(bool);
void calibrateBlack();
void calibrateWhite();
int getError();
int detectJunc();
bool areAllSame(bool);
extern int blackThreshold[NUM_SENSORS];
extern int whiteThreshold[NUM_SENSORS];

#endif