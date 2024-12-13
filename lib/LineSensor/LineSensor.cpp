#include <LineSensor.h>
#include <motorControl.h>

int sensor_array[NUM_SENSORS] = {D1, D2, D3, D4, D5, D6, D7, D8, D9, D10};
int threshold[NUM_SENSORS];
int weights[NUM_SENSORS] = {-7, -5, -3, -1, 0, 0, 1, 3, 5, 7};
int readings[NUM_SENSORS];
int rawReadings[NUM_SENSORS];
bool lost = false;

int blackThreshold[NUM_SENSORS] = {300, 300, 300, 300, 300, 300, 300, 300, 300, 300};
int whiteThreshold[NUM_SENSORS] = {110, 110, 110, 110, 110, 110, 110, 110, 110, 110};
const bool white = true;
const bool black = false;
bool lineColor = white;

float Kp = 6;
float Ki = 0;
float Kd = 0.2;

int error_sumIR = 0;
int error_difIR = 0;
int lastErrorIR = 0;

// black==1
// white=0

bool areAllSame(bool color)
{
    readSensorVals(color);
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        if (!readings[i])
            return false;
    }
    return true;
}

bool isHalfSame(bool color)
{
    readSensorVals(color);
    int rcount = 0;
    for (int i = 5; i < 10; i++)
    {
        if (readings[i])
        {
            rcount++;
        }
    }
    int lcount = 0;
    for (int i = 0; i < 5; i++)
    {
        if (readings[i])
        {
            lcount++;
        }
    }

    if (lcount > 4 or rcount > 4)
    {
        return true;
    }
    return false;
}

void readSensorVals(bool color) // white=true & black=false
{
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        rawReadings[i] = analogRead(sensor_array[i]);
        if (color)
        {
            readings[i] = rawReadings[i] < whiteThreshold[i] ? 1 : 0;
        }
        else
        {
            readings[i] = rawReadings[i] > blackThreshold[i] ? 1 : 0;
        }
        // Serial.print(" - ");
        // Serial.print(readings[i]);
    }
    // Serial.println();
}

int getError(bool color)
{
    readSensorVals(color);
    int sum = 0;
    int totalActivated = 0;

    // Calculate weighted sum of sensor readings
    for (int i = 0; i < NUM_SENSORS; i++)
    {
        if (readings[i])
        { // Set a threshold to determine if a sensor detects the line
            sum += weights[i];
            totalActivated++;
        }
        //    Serial.print(readings[i]);
        //    Serial.print(" - ");
    }
    // If no sensors detect the line, return 0 error (robot is lost)
    if (totalActivated == 0)
    {
        lost = true;
        return 0;
    }
    lost = false;
    // Calculate and return the error
    return sum / totalActivated;
}

void movetoJunction(bool color)
{
    error_sumIR = 0;
    error_difIR = 0;
    lastErrorIR = 0;
    while (true)
    {
        PIDfollow(color);
        if (areAllSame(color) or isHalfSame(color))
        {
            stopMotors();
            delay(1000);
            return;
        }
    }
}

void calibrateBlack()
{
    for (int j = 0; j < NUM_SENSORS; j++)
    {
        // getting sesnsor readings
        int val = analogRead(sensor_array[j]) - 100;
        blackThreshold[j] = val;
    }
    for (int x = 0; x < 300; x++)
    {

        for (int j = 0; j < NUM_SENSORS; j++)
        {
            // getting sesnsor readings
            int val = analogRead(sensor_array[j]) - 100;
            // set the max we found THIS time
            if (blackThreshold[j] < val)
                blackThreshold[j] = val;
        }
        delay(10);
    }
}

void calibrateWhite()
{
    for (int j = 0; j < NUM_SENSORS; j++)
    {
        // getting sesnsor readings
        int val = analogRead(sensor_array[j]) + 20;
        whiteThreshold[j] = val;
    }

    for (int x = 0; x < 100;)
    {

        for (int j = 0; j < NUM_SENSORS; j++)
        {
            // getting sesnsor readings
            int val = analogRead(sensor_array[j]) + 20;
            // set the max we found THIS time
            if (whiteThreshold[j] < val)
                whiteThreshold[j] = val;
        }
        x++;
        delay(10);
    }
}

void PIDfollow(bool color)
{
    int errorIR = getError(color);
    error_sumIR += errorIR;
    error_difIR = errorIR - lastErrorIR;
    int correction = Kp * errorIR + Ki * error_sumIR + Kd * error_difIR;
    int leftSpeed = (baseSpeed + correction);
    int rightSpeed = (baseSpeed - correction);
    leftSpeed = constrain(leftSpeed, -255, 255);
    rightSpeed = constrain(rightSpeed, -255, 255);
    controlMotors(leftSpeed, rightSpeed);
}