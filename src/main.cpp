#include <Arduino.h>
#include <Wire.h>

#include <LineSensor.h>
#include <motorControl.h>

#define buttonPin 19 // Define the pin for the button

//function declarations


// PID constants

//7,0,3
float Kp = 7.5;  // Proportional gain
float Ki = 0.1;  // Integral gain
float Kd = 3;  // Derivative gain


//other variables
int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

// int weights[NUM_SENSORS] = {7,4,2,1,-1,-2,-4,-7};



float error_sum=0;
float error_dif=0;
float lastError=0;

volatile bool stopCalibration = false; // Flag to indicate if calibration should stop



void setup()
{

  Serial.begin(9600);
  Serial.println("Calibrating...");
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(DR, INPUT);
  pinMode(DL, INPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  delay(500);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), stopCalibrationISR, FALLING); // Attach the interrupt to the button
  //calibrate();
  //detachInterrupt(digitalPinToInterrupt(buttonPin)); // Detach the interrupt to the button
}


void loop()
{ // Calculate error
  switch (detectJunc())
  {
  case 1:
    Serial.println("T Junction detected");
    break;
  case 2:
    Serial.println("Right Turn detected");
    break;
  case 3:
    Serial.println("Left Turn detected");;
    break;
  case 4:
    Serial.println("Lost");
    error_sum = 0;
    error_dif = 0;
    break;
  default: // PID line following
    Serial.println("Following Line");
    break;
  }
  delay(500);
}