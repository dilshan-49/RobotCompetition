#ifndef BOXARRANGING_H
#define BOXARRANGING_H

#include <Arduino.h>
#include <LineSensor.h>
#include <motorControl.h>

extern int error;
extern float Kd;
extern float Kp;
extern float Ki;
extern float error_sum;
extern float error_dif;
extern float lastError;

void boxOrdering(int);
void redDecending();
void blueAsending();
void gotoFirstBox();
void gotoSecondBox();
void gotoThirdBox();
void carryBoxTo(int);
void nextMoveUp(int);
void nextMoveDown(int);
int measureHeight();
void blinkLED();
void nextMoveTillWhite();
void lineFollowTillWhite();


#endif