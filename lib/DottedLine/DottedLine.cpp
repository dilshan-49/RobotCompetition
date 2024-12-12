#include <Arduino.h>
#include <LineSensor.h>

/* using pid center the robot , move forward according to line direction without braking at end of the black line*/

int maximum(sensor_array[], 10){
    int max_array_value = 0;
    for i in range(i=0;i<10;i++){
        if (sensor_array[i] > max_array){
            max_array_value = sensor_array[i];
        }
    }
    return max_array_value
}


bool robotInLine(){
    if (max_array_value < 200){
        return true
    }
    else{
        return false
    }

}

void following(){
    if (robotInLine){
        /*follow the line using pid*/
    }
    else{
        /* move forward according to last pid output on line , when half of next line is deteced 
        by ir array using pid robot center the line*/
        if(D1<2 || D2 || D3 || D4 || D5 || D6 || D7 || D8 || D9 || D10 ){ /* or move zig zag */
            /* using pid re-align center to the line*/
            
        }
    }
}