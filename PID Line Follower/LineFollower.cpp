#include <Arduino.h>
#include <Wire.h>


#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN     // no emitter control
#define D1 34
#define D2 35
#define D3 32
#define D4 33
#define D5 25
#define D6 26
#define D7 27
#define D8 14
#define M1 23
#define M2 22
#define M3 15
#define M4 2

void calibrate();

int max_sensor_values[NUM_SENSORS];
int min_sensor_values[NUM_SENSORS];
int sensor_values[NUM_SENSORS];
int sensor_array[NUM_SENSORS]={D1,D2,D3,D4,D5,D6,D7,D8};

void setup()
{

  Serial.begin(9600);
  Serial.println("Calibrating...");
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D7, INPUT);
  pinMode(D8, INPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);
  delay(500);
  calibrate();
}


void loop()
{
  int normalized_values[NUM_SENSORS];
  Serial.print("Sensor :");
  // Read and normalize sensor values
  for (int j = 0; j < NUM_SENSORS; j++) {
    sensor_values[j] = analogRead(sensor_array[j]);
    normalized_values[j] = map(sensor_values[j], min_sensor_values[j], max_sensor_values[j], 100, 0); 
    Serial.print(normalized_values[j]);
    Serial.print(" ");
  }
  Serial.println();
  delay(500);
}

void calibrate()
{
  for (int i = 0; i < 500; i++)
  {
    if ((i % 25) == 0)
      Serial.print(".");

    for (int j = 0;j<NUM_SENSORS;j++)
    {
      //getting sesnsor readings
      sensor_values[j] = analogRead(sensor_array[j]);
    }

      for (int j = 0; j < NUM_SENSORS; j++)
      {
        // set the max we found THIS time
        if ((i == 0) || max_sensor_values[j] < sensor_values[j])
          max_sensor_values[j] = sensor_values[j];

        // set the min we found THIS time
        if ((i == 0) || min_sensor_values[j] > sensor_values[j])
          min_sensor_values[j] = sensor_values[j];
      }
      delay(100);
  }

  Serial.println();
  Serial.println("Max sensor values (calibrated):");
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(max_sensor_values[i]);
    Serial.print(' ');
  }
  Serial.println();

  Serial.println("Min sensor values (calibrated):");
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(min_sensor_values[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
}