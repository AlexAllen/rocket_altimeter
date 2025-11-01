#include <Wire.h>
#include "sensor_suite.h"

SensorSuite sensors;

void setup() {
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.print("Starting up\n");

  sensors.setup();
}

void loop() {

  sensors.update();
  Serial.print(sensors.temp);
  Serial.print(", ");
  Serial.print(sensors.pressure);
  Serial.print(", ");
  Serial.print(sensors.accel[0]);
  Serial.print(", ");
  Serial.print(sensors.accel[1]);
  Serial.print(", ");
  Serial.print(sensors.accel[2]);
  Serial.print(", ");
  Serial.print(sensors.gyro[0]);
  Serial.print(", ");
  Serial.print(sensors.gyro[1]);
  Serial.print(", ");
  Serial.print(sensors.gyro[2]);
  Serial.print(", ");
  Serial.print(sensors.mag[0]);
  Serial.print(", ");
  Serial.print(sensors.mag[1]);
  Serial.print(", ");
  Serial.print(sensors.mag[2]);
  Serial.print("\n");
  
  delay(3000);
}
