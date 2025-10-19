#include "sensor_suite.h"
#include "Arduino.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

SensorSuite::SensorSuite()
{
  temp = 0.0;
  pressure = 0.0;
  accel[0] = 0.0;
  accel[1] = 0.0;
  accel[2] = 0.0;
  gyro[0] = 0.0;
  gyro[1] = 0.0;
  gyro[2] = 0.0;
  mag[0] = 0.0;
  mag[1] = 0.0;
  mag[2] = 0.0;
  
  Serial.print("Starting BNO055\n");
  _bno = Adafruit_BNO055(55);
  if(!_bno.begin())
  {
    Serial.print("Error starting BNO055!\n");
    while(1);
  }
  Serial.print("BNO055 started successfully\n\n");

  Serial.print("Starting BMP280\n");
  if(!_bmp.begin())
  {
    Serial.print("Error starting BMP280!\n");
    while(1);
  }
  Serial.print("BMP280 started successfully\n\n");
}

bool SensorSuite::update()
{
  sensors_event_t event;

  _bmp.getTemperatureSensor()->getEvent(&event);
  temp = event.temperature;

  _bmp.getPressureSensor()->getEvent(&event);
  pressure = event.pressure;

  _bno.getEvent(&event, Adafruit_BNO055::VECTOR_LINEARACCEL);
  accel[0] = event.acceleration.x;
  accel[1] = event.acceleration.y;
  accel[2] = event.acceleration.z;

  _bno.getEvent(&event, Adafruit_BNO055::VECTOR_GYROSCOPE);
  gyro[0] = event.gyro.x;
  gyro[1] = event.gyro.y;
  gyro[2] = event.gyro.z;

  _bno.getEvent(&event, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  mag[0] = event.magnetic.x;
  mag[1] = event.magnetic.y;
  mag[2] = event.magnetic.z;

  return true;
}

