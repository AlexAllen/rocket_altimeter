#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "storage.h"

// SD card CS is on pin 9, flash is on pin 8
Storage storage(9, 8);


void setup() {

  // Get serial ready
  Serial.begin(9600);
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.print("Starting up\n");

  storage.setup();

  Serial.print("Wiping SD card\n");
  storage.wipe_flash();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
