#include <motorControl.h>
#include <LineSensor.h>

#define ENCODER_LEFT 19
#define ENCODER_RIGHT 18

int baseSpeed = 90;

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
  analogWrite(LEFT_PWM, leftSpeed);
  analogWrite(RIGHT_PWM, rightSpeed);
}
//working properly
void stopMotors()
{
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}
//working properly
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
//working properly
void turnLeft(int speed)
{

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), leftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), rightEncoder, RISING);

  encL = 0;
  encR = 0;
   while(encL<130 && encR<130){
     moveForward(100);
   }
   encL = 0;
   encR = 0;

   stopMotors();

  while(encL<150 && encR<150){
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);    
  }
  stopMotors();
}
// working properly
void turnRight(int speed)
{


  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), leftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), rightEncoder, RISING);

  encL = 0;
  encR = 0;
   while(encL<130 && encR<130){
     moveForward(100);
   }
   encL = 0;
   encR = 0;

   stopMotors();

  while(encL<150 && encR<150){
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
  }
  stopMotors();
}

void turnBack(int speed)
{
  encL = 0;
  encR = 0;

  attachInterrupt(digitalPinToInterrupt(ENCODER_LEFT), leftEncoder, RISING);
  attachInterrupt(digitalPinToInterrupt(ENCODER_RIGHT), rightEncoder, RISING);

while(encL<330 && encR<330){ 
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
}
 
  stopMotors();
}

void moveForward(int speed)
{
  
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
  
}

void moveBackward(int speed)
{
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
}
void reverse(int speed)
{
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
  readSensorVals(false);
  while (areAllSame(false))
  {
    readSensorVals(false);
    delay(50);
  }
  brake();
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