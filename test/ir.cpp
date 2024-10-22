#include <Arduino.h>
#include <Wire.h>


#define NUM_SENSORS   8     // number of sensors used
#define D1 A0
#define D2 A1
#define D3 A2
#define D4 A3
#define D5 A4

void setup()
{

  Serial.begin(9600);
  Serial.println("Calibrating...");
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
}

void loop()
{
  int sensor_values[NUM_SENSORS];
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    sensor_values[i] = analogRead(D1 + i);
    Serial.print(sensor_values[i]);
    Serial.print(" ");
  }
  Serial.println();
  delay(200);
}

