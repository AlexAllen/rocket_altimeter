#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>


class SensorSuite
{
  public:
    SensorSuite();
    bool update();

    float temp, pressure;
    float accel[3];
    float gyro[3];
    float mag[3];

  //private:
    Adafruit_BNO055 bno;
    Adafruit_BMP280 bmp;
};

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
  bno = Adafruit_BNO055(55);
  if(!bno.begin())
  {
    Serial.print("Error starting BNO055!\n");
    while(1);
  }
  Serial.print("BNO055 started successfully\n\n");

  Serial.print("Starting BMP280\n");
  if(!bmp.begin())
  {
    Serial.print("Error starting BMP280!\n");
    while(1);
  }
  Serial.print("BMP280 sensorID: ");
  Serial.print(bmp.sensorID());
  Serial.print("\n");
  Serial.print("BMP280 started successfully\n\n");
}

bool SensorSuite::update()
{
  sensors_event_t event;

  bmp.getTemperatureSensor()->getEvent(&event);
  temp = event.temperature;

  bmp.getPressureSensor()->getEvent(&event);
  pressure = event.pressure;

  bno.getEvent(&event, Adafruit_BNO055::VECTOR_LINEARACCEL);
  accel[0] = event.acceleration.x;
  accel[1] = event.acceleration.y;
  accel[2] = event.acceleration.z;

  bno.getEvent(&event, Adafruit_BNO055::VECTOR_GYROSCOPE);
  gyro[0] = event.gyro.x;
  gyro[1] = event.gyro.y;
  gyro[2] = event.gyro.z;

  bno.getEvent(&event, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  mag[0] = event.magnetic.x;
  mag[1] = event.magnetic.y;
  mag[2] = event.magnetic.z;

  return true;
}

SensorSuite *sensors;

void setup() {
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.print("Starting up\n");

  sensors = new SensorSuite();
}

void loop() {

  sensors->update();
  Serial.print(sensors->temp);
  Serial.print(", ");
  Serial.print(sensors->pressure);
  Serial.print(", ");
  Serial.print(sensors->accel[0]);
  Serial.print(", ");
  Serial.print(sensors->accel[1]);
  Serial.print(", ");
  Serial.print(sensors->accel[2]);
  Serial.print(", ");
  Serial.print(sensors->gyro[0]);
  Serial.print(", ");
  Serial.print(sensors->gyro[1]);
  Serial.print(", ");
  Serial.print(sensors->gyro[2]);
  Serial.print(", ");
  Serial.print(sensors->mag[0]);
  Serial.print(", ");
  Serial.print(sensors->mag[1]);
  Serial.print(", ");
  Serial.print(sensors->mag[2]);
  Serial.print("\n");
  
  delay(3000);
}
