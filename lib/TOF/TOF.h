#ifndef TOF_H
#define TOF_H

#include <Wire.h>
#include <Adafruit_VL53L0X.h>

void tof_setup();
void tof_value();

int get_tof_value();
int Find_Box();

#endif
