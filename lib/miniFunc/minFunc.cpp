#include <miniFunc.h>
#include <Wire.h>
#include <pinDefinitions.h>
#include <Adafruit_TCS34725.h>

void displayTask(int CaseNum)
{
    switch (CaseNum)
    {
    case 1:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, LOW);
        break;

    case 2:
        digitalWrite(Red, LOW);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, LOW);
        break;

    case 3:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, LOW);
        break;

    case 4:
        digitalWrite(Red, LOW);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, HIGH);
        break;

    case 5:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, HIGH);
        break;

    case 6:
        digitalWrite(Red, LOW);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, HIGH);
        break;

    case 7:
        digitalWrite(Red, HIGH);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, HIGH);
        break;
    default:
        break;
    }
    delay(1500);
    digitalWrite(Red, LOW);
    digitalWrite(Blue, LOW);
    digitalWrite(Green, LOW);
}

void blinkAll()
{
    for (int i = 0; i < 2; i++)
    {
        digitalWrite(Red, HIGH);
        digitalWrite(Green, HIGH);
        digitalWrite(Blue, HIGH);
        delay(300);
        digitalWrite(Red, LOW);
        digitalWrite(Green, LOW);
        digitalWrite(Blue, LOW);
        delay(300);
    }
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

int detectRedOrBlue()
{
    digitalWrite(TCS34725_POWER_PIN, HIGH);
    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_154MS, TCS34725_GAIN_1X);
    delay(1000);

    uint16_t r, g, b, c;    // Raw color values
    float red, green, blue; // Normalized RGB values

    // Get raw data from the sensor
    tcs.getRawData(&r, &g, &b, &c);

    // Normalize the values (0 to 1) by dividing by the clear channel (c)
    red = (float)r / c;
    green = (float)g / c;
    blue = (float)b / c;
    // Scale to 0-255 for display purposes
    red *= 255;
    green *= 255;
    blue *= 255;
    // Check if the detected color is red or blue
    if (red > blue && red > green && red > 150)
    {
        delay(1000);
        digitalWrite(TCS34725_POWER_PIN, LOW);
        return 0;
    }
    else if (green > red && blue > red)
    {
        delay(1000);
        digitalWrite(TCS34725_POWER_PIN, LOW);
        return 1;
    }
    else
    {
        delay(1000);
        digitalWrite(TCS34725_POWER_PIN, LOW);
        return -1; // If neither red nor blue is dominant
    }
}

bool checkGate()
{
    if (getDistanceFromSensor(2) < 20)
        return true;
    return false;
}