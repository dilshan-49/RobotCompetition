#include <LineSensor.h>
#include <motorControl.h>


int sensor_array[NUM_SENSORS] = {D1, D2, D3, D4, D5, D6, D7, D8};
int threshold[NUM_SENSORS] ;
int weights[NUM_SENSORS + 2] = {0,-7, -4, -2, -1 , 1, 2, 4, 7,0};
int readings[NUM_SENSORS + 2];
int thresholdR;
int thresholdL;
bool black = false;
int cal_array[NUM_SENSORS];

bool areAllBlack(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == 1) {
            return false;
        }
    }
    return true;
}

bool areAllWhite(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        if (array[i] == 0) {
            return false;
        }
    }
    return true;
}

void readSensorVals(){
    readings[0] = analogRead(DR)>thresholdR ? 1 : 0;
    Serial.print(readings[0]);
    for (int i = 0; i <= 7; i++){
        readings[i+1] = analogRead(sensor_array[i])<threshold[i] ? 1 : 0;
        Serial.print(readings[i+1]);  
    }
    
    readings[9] = analogRead(DL)>thresholdL ? 1 : 0;
    Serial.println(readings[9]);
}


int getError() {
    readSensorVals();
    int sum = 0;
    int totalActivated = 0;

    // Calculate weighted sum of sensor readings
    for (int i = 1; i < NUM_SENSORS + 1; i++)
    {
        if (readings[i])
        { // Set a threshold to determine if a sensor detects the line
            sum += weights[i];
            totalActivated++;
        }
        Serial.print(readings[i]);
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
    return sum/totalActivated;
}

int detectJunc(){
    readSensorVals();
    //detect T junc
    if(areAllWhite(readings, 10)){
        return 1;
    }

    //detect Right Turn
    if(areAllWhite(readings, 6)){
        return 2;
    }

    //detect Left Turn
    if(areAllWhite(&readings[4], 6)){
        return 3;
    }
    //Lost the line
    if(areAllBlack(&readings[1], 8)){
        return 4;
    }
    else return 0;
}


