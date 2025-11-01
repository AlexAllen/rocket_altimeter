#include <Wire.h>
#include <SD.h>
#include "sensor_suite.h"

File logfile;
SensorSuite sensors;
unsigned long start_time, loop_start, loop_length;
int period = 50; // time in ms for one loop


void setup() {
  char filename[] = "data_000.csv";

  pinMode(LED_BUILTIN, OUTPUT);
  // turn on LED to show working
  digitalWrite(LED_BUILTIN, LOW); 
  
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.print("Starting up\n");

  // setup sensor suite
  sensors.setup();

  // Fire up SD card
  pinMode(10, OUTPUT);
  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    return;
  }
  Serial.println("SD initialization done.");

  // find free filename
  for(int i=0; i<1000; i++){
    sprintf(filename, "data_%03i.csv", i);
    if(!SD.exists(filename)) break;
  }

  // deal with no file found
  if(filename=="data_999.csv" and !SD.exists(filename)) {
    Serial.print("Failed to find a free filename\n");
    while(1) delay(1);
  }
  
  Serial.print("Found free filename: ");
  Serial.println(filename);

  // open file
  logfile = SD.open(filename, FILE_WRITE);
  if(!logfile) {
    Serial.print("Failed to open file\n");
    while(1) delay(1);
  }
  logfile.print("Time(s),");
  logfile.print("Alt(m),");
  logfile.print("Pressure(Pa),");
  logfile.print("Temp(C),");
  logfile.print("Accel_x(m/s^2),");
  logfile.print("Accel_y(m/s^2),");
  logfile.print("Accel_z(m/s^2),");
  logfile.print("Accel_calibration,");
  logfile.print("Gyro_x(rad/s),");
  logfile.print("Gyro_y(rad/s),");
  logfile.print("Gyro_z(rad/s),");
  logfile.print("Gyro_calibration,");
  logfile.print("Mag_x(uT),");
  logfile.print("Mag_y(uT),");
  logfile.print("Mag_z(uT),");
  logfile.print("Mag_calibration,");
  logfile.print("TaskTime(ms)\n");
  
  start_time = millis();

  Serial.println("Setup complete, into loop");

  // turn on LED to show success
  digitalWrite(LED_BUILTIN, HIGH); 
}

void loop() {
  // Get start time
  loop_start = millis();
  
  // turn on LED to show success
  digitalWrite(LED_BUILTIN, HIGH); 

  // Get new sensor readings
  sensors.update();

  // Now print values
  
  // Time since start up
  logfile.print(0.001*(millis() - start_time));
  logfile.print(",");

  // Altitude
  logfile.print(sensors.alt);
  logfile.print(",");

  // Pressure
  logfile.print(sensors.pressure);
  logfile.print(",");
  
  // Temperature
  logfile.print(sensors.temp);
  logfile.print(",");
  
  // Accel
  for(int i=0; i<3; i++) {
    logfile.print(sensors.accel[i]);
    logfile.print(",");
  }
  logfile.print(sensors.accel_cal);
  logfile.print(",");
  
  // Gyro
  for(int i=0; i<3; i++) {
    logfile.print(sensors.gyro[i]);
    logfile.print(",");
  }
  logfile.print(sensors.gyro_cal);
  logfile.print(",");
  
  // Mag
  for(int i=0; i<3; i++) {
    logfile.print(sensors.mag[i]);
    logfile.print(",");
  }
  logfile.print(sensors.mag_cal);
  logfile.print(",");
  
  // TaskTime
  loop_length = millis() - loop_start;
  logfile.println(loop_length);

  // Finish up
  logfile.flush();

  // wait until next loop 
  delay(period - (millis() - loop_start));
}
