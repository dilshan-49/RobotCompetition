#include <Arduino.h>
#include <Wire.h>


#define NUM_SENSORS 8    // number of sensors used
#define D1 A0
#define D2 A1
#define D3 A2
#define D4 A3
#define D5 A4
#define D6 A5
#define D7 A6
#define D8 A7
#define DR A8
#define DL A9
#define MOTOR_RIGHT_FORWARD 22
#define MOTOR_RIGHT_BACKWARD 23
#define MOTOR_LEFT_FORWARD 25
#define MOTOR_LEFT_BACKWARD 24
#define RIGHT_PWM 6
#define LEFT_PWM 7
#define buttonPin 19 // Define the pin for the button

//function declarations
void calibrate();
void stopCalibrationISR();
int calculateError();
void controlMotors(int leftSpeed, int rightSpeed);
void stopMotors();
void sharpTurn(bool direction);

// PID constants

//7,0,3
float Kp = 7.5;  // Proportional gain
float Ki = 0.1;  // Integral gain
float Kd = 2.5;  // Derivative gain
bool black = false;

//other variables
int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];
int sensor_array[NUM_SENSORS]={D1,D2,D3,D4,D5,D6,D7,D8};
float threshold[NUM_SENSORS] = {800, 800, 800, 800, 800, 800, 800, 800};
// int weights[NUM_SENSORS] = {7,4,2,1,-1,-2,-4,-7};
int weights[NUM_SENSORS] = {7,4,2,1,-1,-2,-4,-7};


float error_sum=0;
float error_dif=0;
float lastError=0;
int baseSpeed =70;
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
{
  // Calculate error
  int error = calculateError();

  // Calculate PID terms
  error_sum += error;
  error_dif = error - lastError;

  // Calculate the control signal
  int correction = Kp * error + Ki * error_sum + Kd * error_dif;

  // Calculate motor speeds based on the correction
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Constrain motor speeds to be within the range of 0-255
  leftSpeed = constrain(leftSpeed, -255, 255);
  rightSpeed = constrain(rightSpeed, -255, 255);
  Serial.print("Error: ");
  Serial.print(error);
  Serial.print("Left Speed: ");
  Serial.print(leftSpeed);
  Serial.print(" Right Speed: ");
  Serial.println(rightSpeed);
  // Set motor speeds
  if (black){
  stopMotors();
  }
  else{
    controlMotors(leftSpeed, rightSpeed);
  }
  //check about the junction
  switch (junctionTurn())
  {
    case 1:
      /* code */
      break;
    case 2:
      /* code */
      break;
    case 3:
      /* code */
      break;
    case 4:
      /* code */
      break;
    default:
      break;
  }
  // Store the last error for the next derivative calculation
  lastError = error;

  delay(20);
  Serial.println();
}

/*
void calibrate()
{ for (int j = 0;j<NUM_SENSORS;j++)
    {
      //getting sesnsor readings
      int val = analogRead(sensor_array[j]);
       max_sensor_values[j] = val;
       min_sensor_values[j] = val;
      }
  while (!stopCalibration)
  {

    for (int j = 0;j<NUM_SENSORS;j++)
    {
      //getting sesnsor readings
      int val = analogRead(sensor_array[j]);
        // set the max we found THIS time
      if (max_sensor_values[j] < val)
        max_sensor_values[j] = val;

        // set the min we found THIS time
      if (min_sensor_values[j] > sensor_values[j])
        min_sensor_values[j] = val;
      }
      delay(100);
  }

  Serial.println();
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    threshold[i]= (max_sensor_values[i] + min_sensor_values[i]) / 2;
    Serial.print(threshold[i]);
    Serial.print(" ");
  }
  Serial.println();
  Serial.println();
}


void stopCalibrationISR() {
  stopCalibration = true; // Set the flag to true when the button is pressed
}

*/

// Function to calculate the error based on sensor readings and weights

int calculateError() {
  int sum = 0;
  int totalActivated = 0;

  // Calculate weighted sum of sensor readings
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (analogRead(sensor_array[i])  < threshold[i]) {  // Set a threshold to determine if a sensor detects the line
      sum += weights[i];
      totalActivated++;
    }
    Serial.print(analogRead(sensor_array[i]));
    Serial.print(" - ");
  }
  Serial.println();
  // If no sensors detect the line, return 0 error (robot is lost)
  if (totalActivated == 0){
    black = true;
    return 0;
  }

  black = false;
  // Calculate and return the error
  return sum / totalActivated;
}

// Function to control the motors based on calculated speeds
void controlMotors(int leftSpeed, int rightSpeed) {
  // Left motor control
  if (leftSpeed > 0) {
    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  } else {
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);
    digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
    leftSpeed = -leftSpeed;
  }
  
  // Right motor control
  if (rightSpeed > 0) {
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  } else {
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
    rightSpeed = -rightSpeed;
  }
  
  // Set motor speeds using PWM
  analogWrite(LEFT_PWM, leftSpeed);
  analogWrite(RIGHT_PWM, rightSpeed);
}

void stopMotors(){
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}

void sharpTurn(bool direction){
  
}
int junctionTurn(){
  int leftcount = 0;
  int rightcount=0;
  //check  whether left sensors detected the white line
  for (int i = 0; i <= 4;i++){
    if(sensor_array[i]<threshold[i]){
      leftcount++;
    }
  }
  //check whether right sensors detected the white line
  for (int i = 3; i <= 7;i++){
    if(sensor_array[i]<threshold[i]){
      rightcount++;
    }
  }
  if(leftcount>3 and rightcount>3){
    //T junction detected
  }
  else if(leftcount>3){
    //turn left
  }
  else if(rightcount>3){
    //turn right
  }

}