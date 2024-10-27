#include <LineSensor.h>
#include <motorControl.h>


int sensor_array[NUM_SENSORS] = {D1, D2, D3, D4, D5, D6, D7, D8};
int threshold[NUM_SENSORS] = {900, 900, 900, 900, 900, 900, 900, 900};
int weights[NUM_SENSORS + 2] = {0,-7, -4, -2, -1 , 1, 2, 4, 7,0};
int readings[NUM_SENSORS + 2];
int thresholdR = 900;
int thresholdL = 900;
bool black = false;



bool areAllOnes(int* array, int size) {
    for (int i = 0; i < size; ++i) {
        if (array[i] != 1) {
            return false;
        }
    }
    return true;
}

void readSensorVals(){
    for (int i = 0; i <= 7; i++){
        readings[i+1] = analogRead(sensor_array[i])<threshold[i] ? 1 : 0;  
    }
    readings[0] = 0;
    readings[9] = 0;
    // if (analogRead(DR)<thresholdR)
    //     readings[0] = 1;
    // else
    //     readings[0] = 0;

    // if (analogRead(DL)<thresholdL)
    //     readings[9] = 1;
    // else
    //     readings[9] = 0;
}

int getError() {
    readSensorVals();
    int sum = 0;
    int totalActivated = 0;

    // Calculate weighted sum of sensor readings
    for (int i = 0; i < NUM_SENSORS + 2; i++)
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
    //detect T junc
    if(areAllOnes(readings, 10)){
        return 1;
    }

    //detect left Turn
    if(areAllOnes(readings, 5)){
        return 2;
    }

    //detect right Turn
    if(areAllOnes(&readings[5], 5)){
        return 3;
    }
    //no junction detected
    else
        return 0;
}


