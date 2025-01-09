#include <motorControl.h>
#include <LineSensor.h>
#include <pinDefinitions.h>

int baseSpeed = 85;

static int error;
static int lastError;
static int errorSum;
static int errorDif;
static int correction;

float KpEn = 1;
float KiEn = 0;
float KdEn = 0.21;

volatile int encL;
volatile int encR;

void rightEncoder()
{
  encR++;
}

void leftEncoder()
{
  encL++;
}

void attachInterrupts()
{
  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), leftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), rightEncoder, RISING);
}

void detachInterrupts()
{
  detachInterrupt(digitalPinToInterrupt(ENCODER_LEFT));
  detachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT));
}

void controlMotors(int leftSpeed, int rightSpeed)
{
  // Left motor control
  if (leftSpeed > 0)
  {
    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  }
  else
  {
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);
    digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
    leftSpeed = -leftSpeed;
  }

  // Right motor control
  if (rightSpeed > 0)
  {
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  }
  else
  {
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
    rightSpeed = -rightSpeed;
  }

  // Set motor speeds using PWM
  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);
  analogWrite(LEFT_PWM, leftSpeed);
  analogWrite(RIGHT_PWM, rightSpeed);
}

static void encoderPID(int caseNum)
{

  error = encL - encR;
  errorSum += error;
  errorDif = error - lastError;
  lastError = error;
  correction = KpEn * error + KiEn * errorSum + KdEn * errorDif;
  correction = constrain(correction, -baseSpeed, baseSpeed);
  int leftspeed;
  int rightspeed;
  switch (caseNum)
  {

  case 1:
    leftspeed = baseSpeed + 20 - correction;
    rightspeed = -(baseSpeed + 20 + correction);
    break;

  case 2:
    leftspeed = -(baseSpeed + 20 - correction);
    rightspeed = baseSpeed + 20 + correction;
    break;
  case 3:
    leftspeed = -(baseSpeed - correction);
    rightspeed = -(baseSpeed + correction);
    break;

  default:
    leftspeed = baseSpeed - correction;
    rightspeed = baseSpeed + correction;
    break;
  }

  controlMotors(leftspeed, rightspeed);
}

void stopMotors()
{
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}
// working properly
void brake()
{
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, 100);
  analogWrite(RIGHT_PWM, 100);
  delay(10);
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}
// working properly
void turnLeft()
{

  attachInterrupts();

  encL = 0;
  encR = 0;
  while (encL < 140 && encR < 140)
  {
    encoderPID(0);
  }

  stopMotors();
  delay(500);
  encL = 0;
  encR = 0;

  while (encL < 125 && encR < 125)
  {
    encoderPID(2);
  }
  suddenRight();
  delay(50);
  stopMotors();
  detachInterrupts();
  delay(500);
}

// Turn Right
// working properly
void turnRight()
{

  attachInterrupts();

  encL = 0;
  encR = 0;
  while (encL < 140 && encR < 140)
  {
    encoderPID(0);
  }

  stopMotors();
  delay(500);
  encL = 0;
  encR = 0;
  while (encL < 125 && encR < 125)
  {
    encoderPID(1);
  }
  suddenLeft();
  delay(50);
  stopMotors();
  detachInterrupts();
  delay(500);
}

void turnBack(bool side)
{
  encL = 0;
  encR = 0;

  attachInterrupts();

  while (encL < 1 && encR < 1)
  {
    encoderPID(0);
  }
  stopMotors();
  delay(100);
  encL = 0;
  encR = 0;

  while (encL < 260 && encR < 260)
  {
    if (side)
      encoderPID(1); // turn from right
    else
      encoderPID(2); // turn from left
  }
  if (side)
  {
    suddenLeft();
  }
  else
  {
    suddenRight();
  }
  delay(50);
  stopMotors();
  detachInterrupts();
  delay(500);
}

void moveForward()
{
  encoderPID(0);
}

void moveBackward()
{
  encoderPID(3);
}
void reverse(int speed)
{
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
}

void rotate()
{
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(LEFT_PWM, 90);
  analogWrite(RIGHT_PWM, 90);
}
void suddenRight()
{
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
}
void suddenLeft()
{
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
}

void moveForwardtillEncoders(int en)
{
  encL = 0;
  encR = 0;
  attachInterrupts();
  while (encR < en && encL < en)
  {
    moveForward();
  }
  stopMotors();
  detachInterrupts();
  delay(500);
}

void moveBackwardtillEncoders(int en)
{
  encL = 0;
  encR = 0;
  attachInterrupts();
  while (encR < en && encL < en)
  {
    moveBackward();
  }
  stopMotors();
  detachInterrupts();
  delay(500);
}