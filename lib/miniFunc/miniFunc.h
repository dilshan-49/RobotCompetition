#ifndef MINIFUNC_H
#define MINIFUNC_H

#include <Arduino.h>
#include <pinDefinitions.h>
#include <LineSensor.h>
#include <motorControl.h>
#include <Ultrasonic.h>

void displayTask(int);
void blinkAll();
int detectRedOrBlue();
bool checkGate();

#endif