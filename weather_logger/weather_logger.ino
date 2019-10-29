/*
  SD card datalogger

 This example shows how to log data from three analog sensors
 to an SD card using the SD library.

 The circuit:
 * analog sensors on analog ins 0, 1, and 2
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created  24 Nov 2010
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include "RTClib.h"

#define DHTPIN 2     // do not connect to pin 0 or pin 1
#define DHTTYPE DHT11   // Define DHT11 module
#define chipSelect 4
RTC_DS1307 rtc;
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;
void setup() {
  
Serial.begin(9600);
  dht.begin();
  bmp.begin();
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1){analogWrite(3, 50);};
  }
  Serial.println("card initialized.");
  rtc.begin();

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    analogWrite(3, 50);
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

}
void loop() {
  DateTime time = rtc.now();
  int t = bmp.readTemperature(); 
  int h = dht.readHumidity();
  float p = bmp.readPressure();
  String dataString = "";
  dataString = time.timestamp(DateTime::TIMESTAMP_FULL);
  dataString += ",";
  dataString += t;
  dataString += ",";
  dataString += h;
  dataString += ",";
  dataString += p;
    // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  File dataFile = SD.open("datalog.txt", FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
    analogWrite(3, 50);
  }
   delay (900000);
   
}
