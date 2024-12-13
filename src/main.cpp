#include <Arduino.h>
#include <Wire.h>
#include <miniFunc.h>
// #include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>
#include <pinDefinitions.h>
#include <RoboArm.h>
#include <MazeSolving.h>
#include <Ultrasonic.h>
#include <Decoder.h>

int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

static int TaskNum = 1;
static int barcodeNum = 0;

float error_sum = 0;
float error_dif = 0;
float lastError = 0;

volatile bool stopCalibration = false; // Flag to indicate if calibration should stop
volatile int enR;
volatile int enL;

void calibrateBlack();
void calibrateWhite();

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void setup()
{

  Serial.begin(9600);
  setupPins();
  Serial.println("Calibrating...");
  rotate();
  calibrateBlack();
  delay(500);
  digitalWrite(Green, HIGH);
  delay(5000);
  digitalWrite(Green, LOW);
  calibrateWhite();
  initializeUltrasonicSensors();
  // change the Line Color based on the Task Number
  if (digitalRead(S7) == LOW)
  {
    TaskNum = 8;
  }
  else if (digitalRead(S6) == LOW)
  {
    TaskNum = 7;
  }
  else if (digitalRead(S5) == LOW)
  {
    TaskNum = 6;
  }
  else if (digitalRead(S4) == LOW)
  {
    TaskNum = 5;
  }
  else if (digitalRead(S3) == LOW)
  {
    TaskNum = 4;
  }
  else if (digitalRead(S2) == LOW)
  {
    TaskNum = 3;
  }
  else if (digitalRead(S1) == LOW)
  {
    TaskNum = 2;
  }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void loop()
{
  displayTask(TaskNum);

  switch (TaskNum)
  {
  case 1:
    int size = ReadingWithPID();
    barcodeNum = getNum(size);
    for (int i = 0; i < barcodeNum; i++)
    {
      digitalWrite(Red, HIGH);
      delay(500);
      digitalWrite(Red, LOW);
      delay(500);
    }
    movetoJunction(white);
    turnRight();
    movetoJunction(white);
    blinkAll();
    TaskNum++;
    break;

  case 2:
    mazeSolve(barcodeNum);
    TaskNum++;
    ;
    break;

  case 3:
    // detect color
    // move forward till line
    // color line follow
    TaskNum++;
    break;

  case 4:
    break;
  }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void calibrateBlack()
{
  digitalWrite(Blue, HIGH);
  for (int j = 0; j < NUM_SENSORS; j++)
  {
    // getting sesnsor readings
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
  digitalWrite(Blue, LOW);
}

void calibrateWhite()
{
  digitalWrite(Red, HIGH);
  for (int j = 0; j < NUM_SENSORS; j++)
  {
    // getting sesnsor readings
    int val = analogRead(sensor_array[j]);
    whiteThreshold[j] = val + 50;
  }
  int x = 0;

  while (x < 100)
  {

    for (int j = 0; j < NUM_SENSORS; j++)
    {
      // getting sesnsor readings
      int val = analogRead(sensor_array[j]);
      // set the max we found THIS time
      if (whiteThreshold[j] - 50 < val)
        whiteThreshold[j] = val + 50;
    }
    x++;
    delay(10);
  }
  digitalWrite(Red, LOW);
}