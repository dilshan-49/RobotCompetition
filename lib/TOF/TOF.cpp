#include <Adafruit_VL53L0X.h> 

#define XSHUT_PIN 7 

Adafruit_VL53L0X lox;

int measurementCount = 0;
const int maxMeasurements = 3;
int tof_distance = 0;
int height;

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
}

int get_tof_value() {
  if (measurementCount < maxMeasurements) {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4) { // Valid measurement
      tof_distance += measure.RangeMilliMeter;
    } else {
      Serial.println("Out of range");
    }
    measurementCount++;
    delay(500); 
  } 
  
  if (measurementCount >= maxMeasurements) {
    int averageDistance = tof_distance / maxMeasurements;
    measurementCount = 0;
    tof_distance = 0;
    return averageDistance;
  }

  return -1; 
}

int Find_Box() {
  height = get_tof_value();

  if (height == -1) {
    // Serial.println("Measurement in progress...");
    return;
  }

  if (height < 120) {
    Serial.println("15cm");
    return 15;
  } else if (height <= 180) { 
    Serial.println("10cm");
    return 10;
  } else if (height <= 250) {
    Serial.println("5cm");
    return 5;
  } else {
    Serial.println("Out of range");
    return 0;
  }
}
