#include <Wire.h>
#include <SD.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

File myFile;
Adafruit_BNO055 bno = Adafruit_BNO055(55);
Adafruit_BMP280 bmp; // use I2C interface
Adafruit_Sensor *bmp_temp = bmp.getTemperatureSensor();
Adafruit_Sensor *bmp_pressure = bmp.getPressureSensor();

void setup() {
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.print("Starting up\n");

  /* Initialise the IMO */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  // Fire up pressure sensor
  unsigned status;
  status = bmp.begin();
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
  }

  // Fire up SD card
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

 
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
  sensors_event_t temp_event, pressure_event, orient_event;
  bmp_temp->getEvent(&temp_event);
  bmp_pressure->getEvent(&pressure_event);
  bno.getEvent(&orient_event);

  Serial.print(temp_event.temperature);
  Serial.print(",");
  Serial.print(pressure_event.pressure);
  Serial.print(",");
  Serial.print(orient_event.orientation.x);
  Serial.print(",");
  Serial.print(orient_event.orientation.y);
  Serial.print(",");
  Serial.print(orient_event.orientation.z);
  Serial.print("\n");
  
  delay(2000);
}
