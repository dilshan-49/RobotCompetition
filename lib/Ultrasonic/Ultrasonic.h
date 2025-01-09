
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <Arduino.h>

#define TRIG1 50
#define ECHO1 51

#define TRIG2 52
#define ECHO2 53

#define TRIG3 28
#define ECHO3 30

class Ultrasonic
{
public:
    Ultrasonic(int trigPin, int echoPin);
    void begin();
    float getDistance();

private:
    int trigPin;
    int echoPin;
};

void initializeUltrasonicSensors();
float getDistanceFromSensor(int sensorNumber);

#endif

