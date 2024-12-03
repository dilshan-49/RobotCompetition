#include <Arduino.h>
#include <Wire.h>

#include <LineSensor.h>
#include <motorControl.h>
#include <Decoder.h>

#define PidR 44
#define RightY 45
#define LeftG 39
#define LostGY 41
#define TjuncB 43
/*
int whiteThreshold[NUM_SENSORS];

// function declarations

// PID constants

// 7,0,3
float Kp = 7;    // Proportional gain
float Ki = 0.05; // Integral gain
float Kd = 2.6;  // Derivative gain

// other variables
int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

// int weights[NUM_SENSORS] = {7,4,2,1,-1,-2,-4,-7};

float error_sum = 0;
float error_dif = 0;
float lastError = 0;

volatile bool stopCalibration = false; // Flag to indicate if calibration should stop

void calibrateBlack();
void calibrateWhite();
*/

void setup()
{

  Serial.begin(9600);
  Serial.println("Calibrating...");
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(PidR, OUTPUT);
  pinMode(RightY, OUTPUT);
  pinMode(LeftG, OUTPUT);
  pinMode(LostGY, OUTPUT);
  pinMode(TjuncB, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
}

void loop()
{ // Calculate error

  int n = startReading();

  int num = getNum(n);

  Serial.print("Number is ");
  Serial.println(num);
}
