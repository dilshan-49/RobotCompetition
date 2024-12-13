#include <Arduino.h>
#include <Wire.h>

#include <LineSensor.h>
#include <motorControl.h>


int whiteThreshold[NUM_SENSORS];

// function declarations

// PID constants

// 7,0,3
float Kp = 7;    // Proportional gain
float Ki = 0.05; // Integral gain
float Kd = 2.6;  // Derivative gain

// other variables
int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];

// int weights[NUM_SENSORS] = {7,4,2,1,-1,-2,-4,-7};

static float error_sum = 0;
static float error_dif = 0;
static float lastError = 0;




/* using pid center the robot , move forward according to line direction without braking at end of the black line*/

// int maximum(sensor_array[], 10){
//     int max_array_value = 0;
//     for i in range(i=0;i<10;i++){
//         if (sensor_array[i] > max_array){
//             max_array_value = sensor_array[i];
//         }
//     }
//     return max_array_value
// }


// bool robotInLine(){
//     if (max_array_value < 200){
//         return true
//     }
//     else{
//         return false
//     }

// }

void following(){
    if (!areAllSame(black)){
        /*follow the line using pid*/
        PID_follow();
        
    }
    else{
        moveForward(baseSpeed);
    }
}

void PID_follow(){
    // Serial.println("Following Line");
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
}