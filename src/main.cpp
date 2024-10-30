#include <Arduino.h>
#include <Wire.h>

#include <LineSensor.h>
#include <motorControl.h>

#define PidR 44
#define RightY 45
#define LeftG 39
#define LostGY 41
#define TjuncB 43

int whiteThreshold[NUM_SENSORS];

//function declarations


// PID constants

//7,0,3
float Kp = 7;  // Proportional gain
float Ki = 0.05;  // Integral gain
float Kd = 2.6;  // Derivative gain


//other variables
int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

// int weights[NUM_SENSORS] = {7,4,2,1,-1,-2,-4,-7};



float error_sum=0;
float error_dif=0;
float lastError=0;

volatile bool stopCalibration = false; // Flag to indicate if calibration should stop

void calibrateBlack();
void calibrateWhite();
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
  rotate();
  calibrateBlack();
  stopMotors();
  digitalWrite(TjuncB, HIGH);
  delay(5000);
  digitalWrite(TjuncB, LOW);
  calibrateWhite();
  digitalWrite(TjuncB, HIGH);
  delay(1000);
  digitalWrite(TjuncB, LOW);
  for (int i = 0; i < NUM_SENSORS;i++){
    Serial.print(threshold[i]);
    Serial.print(" - ");
  }
  Serial.println("Whites");

  for (int i = 0; i < NUM_SENSORS;i++){
    Serial.print(whiteThreshold[i]);
    Serial.print(" - ");
  }
  Serial.println();

  // attachInterrupt(digitalPinToInterrupt(buttonPin), stopCalibrationISR, FALLING); // Attach the interrupt to the button
  // calibrate();
  delay(1000);
  // detachInterrupt(digitalPinToInterrupt(buttonPin)); // Detach the interrupt to the button
}


void loop()
{ // Calculate error

  digitalWrite(PidR, LOW);
  digitalWrite(RightY, LOW);
  digitalWrite(LeftG, LOW);
  digitalWrite(LostGY, LOW);
  digitalWrite(TjuncB, LOW);
  if (analogRead(D4)<whiteThreshold[3] || analogRead(D5)<whiteThreshold[4]){
    brake();
    delay(500);
    digitalWrite(PidR, HIGH);
    delay(500);
  }
  else{
  switch (detectJunc())
  {
  case 1: //T junction
    digitalWrite(TjuncB, HIGH);
    Serial.println("T Junction");
    moveForward(baseSpeed);
    delay(300);
    stopMotors();
    break;
  case 2: // Right turn
    digitalWrite(RightY, HIGH);
    Serial.println("Right Turn");
     delay(30);
     if (analogRead(D8)<threshold[7]){
       moveForward(baseSpeed);
       delay(200);
       stopMotors();
     }
     else {
      stopMotors();
      turnRight(85, 60);
    }
    
    break;

  case 3: // Left turn
    digitalWrite(LeftG, HIGH);
    Serial.println("Left Turn");
    delay(30);
      if (analogRead(D1)<threshold[0]){
        moveForward(baseSpeed);
        delay(200);
        stopMotors();
      }
      else {
       stopMotors();
       turnLeft(85,60);
     }
    
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
  }
}


void calibrateBlack()
{ for (int j = 0;j<NUM_SENSORS;j++)
    {
      //getting sesnsor readings
      int val = analogRead(sensor_array[j]);
       min_sensor_values[j] = val;
    }
    int x = 0;
    while (x < 300)
      {

        for (int j = 0; j < NUM_SENSORS; j++)
        {
          // getting sesnsor readings
          int val = analogRead(sensor_array[j]);
          // set the max we found THIS time
          if (max_sensor_values[j] < val)
            max_sensor_values[j] = val;

          // set the min we found THIS time
          if (min_sensor_values[j] > sensor_values[j])
            min_sensor_values[j] = val;
        }
        delay(10);
        x++;
      }

}

void calibrateWhite(){
  for (int j = 0; j < NUM_SENSORS; j++)
  {
    // getting sesnsor readings
    int val = analogRead(sensor_array[j]);
    whiteThreshold[j] = val+50;
  }
    int x = 0;
    
  
      while (x < 100)
      {

        for (int j = 0; j < NUM_SENSORS; j++)
        {
          // getting sesnsor readings
          int val = analogRead(sensor_array[j]);
          // set the max we found THIS time
          if (whiteThreshold[j]-50 < val)
            whiteThreshold[j] = val+50;
        }
        x++;
        delay(10);
      }    
}