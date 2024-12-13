#include <Arduino.h>
#include <Wire.h>
// #include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>

#include <RoboArm.h>
#include <MazeSolving.h>
#include <Ultrasonic.h>
#include <Decoder.h>

#define Blue 33
#define Green 31
#define Red 29

// function declarations

// PID constants

// 7,0,3
float Kp = 5; // Proportional gain
float Ki = 0; // Integral gain
float Kd = 3; // Derivative gain

// other variables
int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

// int weights[NUM_SENSORS] = {7,4,2,1,-1,-2,-4,-7};

float error_sum = 0;
float error_dif = 0;
float lastError = 0;

volatile bool stopCalibration = false; // Flag to indicate if calibration should stop
volatile int enR;
volatile int enL;

void left()
{
  enL++;
}

void right()
{
  enR++;
}

void setup()
{

  Serial.begin(9600);
  Serial.println("Calibrating...");

  initializeUltrasonicSensors();
}

void loop()
{
  Serial.println(getDistanceFromSensor(1));
  delay(1000);
}
