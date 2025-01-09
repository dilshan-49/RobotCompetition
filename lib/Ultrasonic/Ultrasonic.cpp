#include <Ultrasonic.h>

Ultrasonic sensor1(TRIG1, ECHO1);
Ultrasonic sensor2(TRIG2, ECHO2);

Ultrasonic::Ultrasonic(int trigPin, int echoPin)
{
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}

void Ultrasonic::begin()
{
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float Ultrasonic::getDistance()
{
    long duration;
    float distance;

    // Clear the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Set the trigPin HIGH for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Read the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distance = duration * 0.034 / 2;

    return distance;
}

void initializeUltrasonicSensors()
{
    sensor1.begin();
    sensor2.begin();
}

float getDistanceFromSensor(int sensorNumber)
{
    switch (sensorNumber)
    {
    case 1:
        return sensor1.getDistance();
    case 2:
        return sensor2.getDistance();
    default:
        return -1; // Invalid sensor number
    }
}
