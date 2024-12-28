#ifndef LINE_SENSOR_H
#define LINE_SENSOR_H

#include <Arduino.h>
#include <pinDefinitions.h>

extern int sensor_array[NUM_SENSORS];
extern int readings[NUM_SENSORS];
extern int threshold[NUM_SENSORS];
extern const bool white;
extern const bool black;

extern float Kp;
extern float Ki;
extern float Kd;

void readSensorVals(bool);
void calibrateBlack();
void calibrateWhite();
int getError(bool);
void movetoJunction(bool);
bool areAllSame(bool);
bool isHalfSame(bool);
void PIDfollow(bool);
void colorLineFollow();
bool leftsame();
bool rightsame();
void ResetErrors();
bool leftHalfBlack();
extern int blackThreshold[NUM_SENSORS];
extern int whiteThreshold[NUM_SENSORS];

#endif