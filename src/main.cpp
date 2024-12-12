#include <Arduino.h>
#include <Wire.h>
#include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>
#include <RoboArm.h>
// #include <Decoder.h>

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
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(D9, INPUT);
  pinMode(D10, INPUT);
  pinMode(Green, OUTPUT);
  pinMode(Red, OUTPUT);
  pinMode(Blue, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  pinMode(LEFT_PWM, OUTPUT);
  pinMode(RIGHT_PWM, OUTPUT);

  // calibrateBlack();
  // calibrateWhite();
  // for (int i = 0; i < NUM_SENSORS; i++)
  // {
  //   threshold[i] = (blackThreshold[i] + whiteThreshold[i]) / 2;
  // }
}

void loop()
{

  //controlMotors(100,100);
  // if(areAllSame(black)){
  //   Serial.println("Black");
  // }
  // else{
  //   Serial.println("White");
  // }
  
  // if (areAllSame(black))
  // {
  //   turnBack(90);
  // }
  initializeArm();
  delay(2000);
  grabBox();
  while(true){

  }
  initializeArm();
  delay()
}
