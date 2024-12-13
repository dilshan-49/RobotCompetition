#include <Arduino.h>
#include <Wire.h>
#include <miniFunc.h>
#include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>
#include <pinDefinitions.h>
#include <RoboArm.h>
#include <MazeSolving.h>
#include <Ultrasonic.h>
#include <Decoder.h>
#include <Adafruit_TCS34725.h>

int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

static int TaskNum = 1;
static int barcodeNum = 0;
static int order;

float error_sum = 0;
float error_dif = 0;
float lastError = 0;

volatile bool stopCalibration = false; // Flag to indicate if calibration should stop
volatile int enR;
volatile int enL;

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
    blinkAll();
    TaskNum++;
    break;

  case 2:
    movetoJunction(white);
    mazeSolve(barcodeNum);
    TaskNum++;
    ;
    break;

  case 3:
    int colorSense = detectRedOrBlue();
    movetoJunction(white);
    encL, encR = 0;
    while (areAllSame(white))
      moveForward();
    stopMotors();
    colorLineFolow();
    TaskNum++;
    break;

  case 4:
    break;
  }
}
