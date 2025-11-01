#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include "storage.h"


bool fireup_storage(int pin) {
  pinMode(pin, OUTPUT);
  if (!SD.begin(pin)) {
    Serial.println("initialization failed on pin ");
    Serial.println(pin);
    return false;
  }
  Serial.println("initialization done.");
  return true;
}

bool empty_dir(char filename[]) {
  Serial.print("in empty_dir for ");
  Serial.print(filename);
  Serial.print("\n");
  File root_obj = SD.open(filename);
  File entry = root_obj.openNextFile();
  while(entry)
  {
    Serial.print("in while loop for ");
    Serial.print(filename);
    Serial.print(" entry is ");
    Serial.print(entry.name());
    Serial.print("\n");
    if(entry.isDirectory())
    {
      empty_dir(entry.name());
      SD.rmdir(entry.name());
    }
    else SD.remove(entry.name());
    
    entry = root_obj.openNextFile();
  }
  return true;
}

Storage::Storage(int sd_pin, int flash_pin) {
  _sd_pin = sd_pin;
  _flash_pin = flash_pin;
}


bool Storage::setup() {
  if(!fireup_storage(_flash_pin)) return false;
  
  return true;
}


bool Storage::transfer(char filename[]) {
  return false;
}


bool Storage::wipe_flash() {
  Serial.print("In wipe_flash()\n");
  // test this on sd card first:
  if(!fireup_storage(_sd_pin)) return false;

  return empty_dir("/");
}
