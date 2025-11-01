#include "sensor_suite.h"
#include "Arduino.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

SensorSuite::SensorSuite()
{
  groundLevelhPa = 0.0;
  temp = 0.0;
  pressure = 0.0;
  alt = 0.0;
  accel[0] = 0.0;
  accel[1] = 0.0;
  accel[2] = 0.0;
  gyro[0] = 0.0;
  gyro[1] = 0.0;
  gyro[2] = 0.0;
  mag[0] = 0.0;
  mag[1] = 0.0;
  mag[2] = 0.0;
}


bool SensorSuite::setup()
{
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

  Serial.print("Determining sea level pressure\n");
  float pressure_sum;
  sensors_event_t event;
  for(int i=0; i<50; i++){
    _bmp.getPressureSensor()->getEvent(&event);
    pressure_sum += event.pressure;
  }
  groundLevelhPa = pressure_sum/50.0;  
  Serial.print("Sea level pressure is ");
  Serial.print(groundLevelhPa);
  Serial.print("hPa\n\n");

  delay(3000);
  Serial.print("Is BNO055 fully calibrated: ");
  Serial.println(_bno.isFullyCalibrated());
}

bool SensorSuite::update()
{
  sensors_event_t event;
   
  temp = _bmp.readTemperature();
  pressure = _bmp.readPressure();
  alt = _bmp.readAltitude(groundLevelhPa);

  _bno.getCalibration(&sys_cal, &gyro_cal, &accel_cal, &mag_cal);

  _bno.getEvent(&event, Adafruit_BNO055::VECTOR_ACCELEROMETER);
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
