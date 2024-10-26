#include <motorControl.h>


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
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, 0);
  analogWrite(RIGHT_PWM, 0);
}
void turnLeft(int speed){
  digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
  digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
  digitalWrite(MOTOR_LEFT_FORWARD, LOW);
  digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
  delay(500);//just keep delay need to measure the time to take turn
  stopMotors();
}
void turnRight(int speed){
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
  delay(500);//just keep delay need to measure the time to take turn
  stopMotors();
}
void turnBack(int speed){
  digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
  digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
  digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
  digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
  analogWrite(LEFT_PWM, speed);
  analogWrite(RIGHT_PWM, speed);
  delay(1000);//just keep delay need to measure the time to take turn
  stopMotors();
}

void rotate(bool direction){
  if(direction){
    digitalWrite(MOTOR_RIGHT_FORWARD, HIGH);
    digitalWrite(MOTOR_RIGHT_BACKWARD, LOW);
    digitalWrite(MOTOR_LEFT_FORWARD, LOW);
    digitalWrite(MOTOR_LEFT_BACKWARD, HIGH);
    analogWrite(LEFT_PWM, 50);
    analogWrite(RIGHT_PWM, 50);
  }else{
    digitalWrite(MOTOR_RIGHT_FORWARD, LOW);
    digitalWrite(MOTOR_RIGHT_BACKWARD, HIGH);
    digitalWrite(MOTOR_LEFT_FORWARD, HIGH);
    digitalWrite(MOTOR_LEFT_BACKWARD, LOW);
    analogWrite(LEFT_PWM, 50);
    analogWrite(RIGHT_PWM, 50);
  }
}