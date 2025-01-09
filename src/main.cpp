#include <Arduino.h>
#include <Wire.h>
#include <miniFunc.h>
#include <BoxArranging.h>
#include <LineSensor.h>
#include <motorControl.h>
#include <pinDefinitions.h>
#include <RoboArm.h>
#include <virtualBox.h>
#include <Ultrasonic.h>
#include <Decoder.h>
#include <Adafruit_TCS34725.h>

int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

static int TaskNum = 1;
static int barcodeNum = 0;
static int order = 1;
static int colorSense;
int x;

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

  if (digitalRead(S8) == LOW)
  {
    digitalWrite(Red, HIGH);
    delay(1000);
    calibrateBlack();
    digitalWrite(Red, LOW);
    delay(2000);
    digitalWrite(Green, HIGH);
    calibrateWhite();
    digitalWrite(Green, LOW);
  }

  initializeUltrasonicSensors();
  // // change the Line Color based on the Task Number
  if (digitalRead(S7) == LOW)
  {
    TaskNum = 8;
  }
  else if (digitalRead(S6) == LOW)
  {
    Serial.println("S6");
    TaskNum = 7;
  }
  else if (digitalRead(S5) == LOW)
  {
    Serial.println("S5");
    TaskNum = 6;
  }
  else if (digitalRead(S4) == LOW)
  {
    Serial.println("S4");
    TaskNum = 5;
  }
  else if (digitalRead(S3) == LOW)
  {
    Serial.println("S3");
    TaskNum = 4;
  }
  else if (digitalRead(S2) == LOW)
  {
    Serial.println("S2");
    TaskNum = 3;
  }
  else if (digitalRead(S1) == LOW)
  {
    Serial.println("S1");
    TaskNum = 2;
  }
  // blinkAll();
  // delay(1000);
  blinkAll();
  encL = 0;
  encR = 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

void loop()
{

  displayTask(TaskNum);
  Serial.println(TaskNum);

  switch (TaskNum)
  {
  case 1: // barcode
  {
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
  }

  case 2: // Maze
  {
    Serial.println("Case 2");
    movetoJunction(white);
    doAllshitin1(barcodeNum);
    blinkAll();
    TaskNum++;
    break;
  }

  case 3: // ColorLine Follow
  {
    bool flag2 = true;

    colorSense = colorx;
    encL, encR = 0;

    moveForwardtillEncoders(15);
    stopMotors();
    while (flag2)
    {
      if (rightsame())
        turnRight();
      else if (leftsame())
        turnLeft();
      else if (areAllSame(white))
      {
        moveForwardtillEncoders(25);
        if (areAllSame(white))
        {
          flag2 = false;
          blinkAll();
        }
        else
        {
          PIDfollow(white);
        }
      }
      // colorLineFollow();
      blinkAll();
      TaskNum++;
      break;
    }
  }
  case 4: // Dotted Line Follow
  {
    baseSpeed = 75;
    while (true)
    {
      if (areAllSame(white))
      {
        stopMotors();
        delay(100);
        blinkAll();
        TaskNum++;
        baseSpeed = 85;
        break;
      }
      else
      {
        PIDfollow(white);
        if (areAllSame(black))
        {
          moveForwardtillEncoders(20);
        }
      }
    }
    // {
    //   /* code */
    //     bool flag=true

    //     while (!areAllSame(black))
    //     {
    //       if (areAllSame(white))
    //       {
    //         stopMotors();
    //         delay(100);
    //         blinkAll();
    //         TaskNum++;
    //         baseSpeed = 85;
    //         break;
    //       }
    //       PIDfollow(white);
    //     }

    //     moveForwardtillEncoders(20);
    // }
  }

  case 5: // gate
  {

    while (checkGate())
    {
      delay(50);
    }

    while (areAllSame(white) || areAllSame(black))
    {
      encL, encR = 0;
      attachInterrupts();
      moveForward();
    }
    detachInterrupts();
    encL = encR = 0;

    moveForward();
    delay(1500);
    stopMotors();
    if (areAllSame(white) || areAllSame(black))
    {
      digitalWrite(Red, HIGH);
    }
    else
    {
      digitalWrite(Blue, HIGH);
    }

    blinkAll();
    TaskNum++;
    break;
  }

  case 6:
  {
    boxOrdering(order);
    ResetErrors();
    while (!areAllSame(black))
    {

      PIDfollow(black);
    }

    break;
  }
  case 7:
    armInitializing();
    encL = 0;
    encR = 0;
    while (!isHalfSame(black))
    {
      moveForward();
    }
    stopMotors();
    delay(500);
    turnLeft();
    // float dist = getDistanceFromSensor(2);
    while (!areAllSame(white))
    {
      moveForward();
    }
    stopMotors();
    delay(300);
    grabBox();
    turnBack(true);
    while (!areAllSame(black))
    {
      encL = 0;
      encR = 0;
      attachInterrupts();
      moveForward();
    }
    stopMotors();
    detachInterrupts();
    turnRight();
    movetoJunction(black);
    movetoJunction(black);
    turnRight();
  }
  while (!areAllSame(white))
  {
    PIDfollow(black);
  }
  turnBack(false);
  while (!areAllSame(black))
  {
    encL = 0;
    encR = 0;
    attachInterrupts();
    moveForward();
  }
  turnRight();
  moveForwardtillEncoders(50);
  releaseBox();
  moveForwardtillEncoders(50);
  encL = 0;
  encR = 0;
  while (!isHalfSame(black))
  {
    moveBackward();
  }
  turnLeft();
}
