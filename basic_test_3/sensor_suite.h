#include "Arduino.h"
#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>


#ifndef SENSOR_SUITE

	class SensorSuite
	{
	  public:
		SensorSuite();
		bool setup();
		bool update();

		float temp, pressure;
		float accel[3];
		float gyro[3];
		float mag[3];

	  private:
		Adafruit_BNO055 _bno;
		Adafruit_BMP280 _bmp;
	};

	#define SENSOR_SUITE 1
#endif