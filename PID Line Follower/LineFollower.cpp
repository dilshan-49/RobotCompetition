#include <Arduino.h>
#include <Wire.h>


#define NUM_SENSORS   8     // number of sensors used
#define D8 A0
#define D7 A1
#define D6 A2
#define D5 A3
#define D4 A4
#define D3 A5
#define D2 A6
#define D1 A7
#define MOTOR_RIGHT_FORWARD 23
#define MOTOR_RIGHT_BACKWARD 22
#define MOTOR_LEFT_FORWARD 24
#define MOTOR_LEFT_BACKWARD 25
#define RIGHT_PWM 6
#define LEFT_PWM 7
#define buttonPin 19 // Define the pin for the button

//function declarations
void calibrate();
void stopCalibrationISR();
float calculateError();
void controlMotors(int leftSpeed, int rightSpeed,bool forward);

// PID constants
float Kp = 1.5;  // Proportional gain
float Ki = 0.0;  // Integral gain
float Kd = 0.5;  // Derivative gain

//other variables
int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];
int sensor_array[NUM_SENSORS]={D1,D2,D3,D4,D5,D6,D7,D8};
float threshold[NUM_SENSORS];
int weights[NUM_SENSORS] = {-20, -15, -10, -5, 5, 10, 15, 20};

float error_sum=0;
float error_dif=0;
float lastError=0;
int baseSpeed = 190;
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
  attachInterrupt(digitalPinToInterrupt(buttonPin), stopCalibrationISR, FALLING); // Attach the interrupt to the button
  calibrate();
  detachInterrupt(digitalPinToInterrupt(buttonPin)); // Detach the interrupt to the button
}


void loop()
{
  // Calculate error
  float error = calculateError();

  // Calculate PID terms
  error_sum += error;
  error_dif = error - lastError;

  // Calculate the control signal
  float correction = Kp * error + Ki * error_sum + Kd * error_dif;

  // Calculate motor speeds based on the correction
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Constrain motor speeds to be within the range of 0-255
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  // Set motor speeds
  controlMotors(leftSpeed, rightSpeed, true);

  // Store the last error for the next derivative calculation
  lastError = error;

  delay(10);  // Short delay for stability
}

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


// Function to calculate the error based on sensor readings and weights
float calculateError() {
  int sum = 0;
  int totalActivated = 0;

  // Calculate weighted sum of sensor readings
  for (int i = 0; i < NUM_SENSORS; i++) {
    if (analogRead(sensor_array[i])  < threshold[i]) {  // Set a threshold to determine if a sensor detects the line
      sum += weights[i];
      totalActivated++;
    }
  }

  // If no sensors detect the line, return 0 error (robot is lost)
  if (totalActivated == 0) return 0;

  // Calculate and return the error
  return sum / totalActivated;
}

// Function to control the motors based on calculated speeds
void controlMotors(int leftSpeed, int rightSpeed,bool forward) {
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