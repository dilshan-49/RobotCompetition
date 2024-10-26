#include <LineSensor.h>
#include <motorControl.h>

bool areAllOnes(const int* array, int size) {
    for (int i = 0; i < size; ++i) {
        if (array[i] != 1) {
            return false;
        }
    }
    return true;
}

void readSensorVals(){
    for (int i = 0; i <= 7; i++){
        if (analogRead(sensor_array[i])<threshold[i])
            readings[i+1] = 1;
        else
            readings[i+1] = 0;    
    }
    if (analogRead(DR)<thresholdR)
        readings[0] = 1;
    else
        readings[0] = 0;

    if (analogRead(DL)<thresholdL)
        readings[9] = 1;
    else
        readings[9] = 0;
}

int getError() {
  int sum = 0;
  int totalActivated = 0;

  // Calculate weighted sum of sensor readings
  for (int i = 0; i < NUM_SENSORS+2; i++) {
    if (readings[i]) {  // Set a threshold to determine if a sensor detects the line
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


