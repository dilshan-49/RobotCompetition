#ifndef BOXARRANGING_H
#define BOXARRANGING_H

#include <Arduino.h>
#include <LineSensor.h>
#include <motorControl.h>

extern int error;
extern float kp;
extern float ki;
extern float kd;

void boxOrdering(int);
void redDecending();
void blueAsending();
void gotoFirstBox();
void gotoSecondBox();
void gotoThirdBox();
void carryBoxTo(int);
void nextMoveUp(int);
void nextMoveDown(int);
void movetoJunction();
int measureHeight();

#endif