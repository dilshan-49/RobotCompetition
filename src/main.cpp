#include <Arduino.h>
#include <Wire.h>

#include <LineSensor.h>
#include <motorControl.h>

#define PidR 44
#define RightY 45
#define LeftG 39
#define LostGY 41
#define TjuncB 43

//function declarations


// PID constants

//7,0,3
float Kp = 7;  // Proportional gain
float Ki = 0.05;  // Integral gain
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
  pinMode(PidR, OUTPUT);
  pinMode(RightY, OUTPUT);
  pinMode(LeftG, OUTPUT);
  pinMode(LostGY, OUTPUT);
  pinMode(TjuncB, OUTPUT);
  pinMode(MOTOR_RIGHT_FORWARD, OUTPUT);
  pinMode(MOTOR_RIGHT_BACKWARD, OUTPUT);
  pinMode(MOTOR_LEFT_FORWARD, OUTPUT);
  pinMode(MOTOR_LEFT_BACKWARD, OUTPUT);
  delay(500);
  //attachInterrupt(digitalPinToInterrupt(buttonPin), stopCalibrationISR, FALLING); // Attach the interrupt to the button
  //calibrate();
 // delay(1000);
  //detachInterrupt(digitalPinToInterrupt(buttonPin)); // Detach the interrupt to the button
}


void loop()
{ // Calculate error
  digitalWrite(PidR, LOW);
  digitalWrite(RightY, LOW);
  digitalWrite(LeftG, LOW);
  digitalWrite(LostGY, LOW);
  digitalWrite(TjuncB, LOW);
  switch (detectJunc())
  {
  case 1: //T junction
    digitalWrite(TjuncB, HIGH);
    Serial.println("T Junction");
    moveForward(baseSpeed);
    delay(400);
    stopMotors();
    break;
  case 2: // Right turn
    digitalWrite(RightY, HIGH);
    Serial.println("Right Turn");
    delay(50);
    if (analogRead(DL)>80){
      moveForward(baseSpeed);
      delay(400);
      stopMotors();
    }
    else turnRight(100,50);
    break;
  case 3: // Left turn
    digitalWrite(LeftG, HIGH);
    Serial.println("Left Turn");
    delay(30);
    if (analogRead(DR)>80){
      moveForward(baseSpeed);
      delay(400);
      stopMotors();
    }
    else turnLeft(100,50);
    break;
  case 4: // Lost
    digitalWrite(LostGY, HIGH);
    Serial.println("Lost");
    error_sum = 0;
    error_dif = 0;
    reverse(65);
    break;
  default: // PID line following
    digitalWrite(PidR, HIGH);
    Serial.println("Following Line");
    int error = getError();

// Calculate PID terms
    error_sum += error;
    error_dif = error - lastError;

    // Calculate the control signal
    int correction = Kp * error + Ki * error_sum + Kd * error_dif;

    // Calculate motor speeds based on the correction
    int leftSpeed = baseSpeed - correction;
    int rightSpeed = baseSpeed + correction;

    // Constrain motor speeds to be within the range of 0-255
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    controlMotors(leftSpeed, rightSpeed);
    lastError = error;

    break;

  }
  //delay(500);
}