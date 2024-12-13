#include <Wire.h>
#include <Adafruit_VL53L0X.h>
#include <TOF.h>

#define XSHUT_PIN 7 

Adafruit_VL53L0X lox;

int measurementCount = 0; 
const int maxMeasurements = 10;

int tof_distance;

void tof_setup() {
  Serial.begin(115200);

  pinMode(XSHUT_PIN, OUTPUT);
  digitalWrite(XSHUT_PIN, HIGH); 
  delay(10); 

  Wire.begin();

 
  if (!lox.begin()) {
    Serial.println("Failed to initialize VL53L0X sensor!");
    while (1);
  }
 // Serial.println("VL53L0X Ready!");
}

int tof_value() {
  if (measurementCount < maxMeasurements) {
    digitalWrite(XSHUT_PIN, HIGH); 
    delay(10); 

    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4) { // If measurement is valid
      tof_distance += measure.RangeMilliMeter;
    //   Serial.println(measure.RangeMilliMeter);
    } else {
      Serial.println("Out of range");
    }

    measurementCount++;
    delay(500); // Delay to control the measurement frequency
  } else {
    // Turn off the sensor after reaching the measurement limit
    digitalWrite(XSHUT_PIN, LOW); // Turn off the sensor
    // Serial.println("Sensor turned off after completing measurements.");
    while (1); // Stop further execution
  }
  return tof_distance;
}
