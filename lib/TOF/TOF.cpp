#include <TOF.h>
#include <Adafruit_VL53L0X.h>
#include <pinDefinitions.h>

Adafruit_VL53L0X lox;

int height;

void tof_setup()
{
  delay(10);
  digitalWrite(XSHUT_PIN, HIGH);
  Wire.begin();

  if (!lox.begin())
  {
    Serial.println("Failed to initialize VL53L0X sensor!");
    while (1)
      ;
  }
}

int get_tof_value()
{
  int count = 0;
  int tof_distance = 0;
  while (count < 3)
  {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4)
    { // Valid measurement
      tof_distance += measure.RangeMilliMeter;
      count++;
      delay(500);
    }
    else
    {
      Serial.println("Out of range");
    }
  }
  int averageDistance = tof_distance / count;
  tof_distance = 0;
  return averageDistance;
}

int Find_Box()
{
  tof_setup();
  height = get_tof_value();
  digitalWrite(XSHUT_PIN, LOW);

  if (height < 120)
  {
    Serial.println("15cm");
    return 15;
  }
  else if (height <= 180)
  {
    Serial.println("10cm");
    return 10;
  }
  else if (height <= 230)
  {
    Serial.println("5cm");
    return 5;
  }
  else
  {
    Serial.println("Out of range");
    return 0;
  }
}
