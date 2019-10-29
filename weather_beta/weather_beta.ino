// annemometer/hall sensor
// vcc to 5v
// gnd to gnd
// sig to 9
  
// RTC tiny rtc module
// Gnd to Gnd
// Vcc t 5v
// Scl to A5
// Sda to A4

// DHT 11
// pin 1 to vcc
// pin 2 to pin 3
// pin 3 not connected
// pin 4 to gnd

// Connect VCC of the BMP180 sensor to 3.3V (NOT 5.0V!)
// Connect GND to Ground
// Connect SCL to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 5
// Connect SDA to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc thats Analog 4
// EOC is not used, it signifies an end of conversion
// XCLR is a reset pin, also not used here

// SD card attached to SPI bus as follows:
// MOSI - pin 11
// MISO - pin 12
// CLK - pin 13
// CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

// libraries needed
#include <Wire.h> // Communications
#include <Adafruit_BMP085.h> //Baromic Presssure
#include <SPI.h>// Communications
#include <SD.h>// Sd
#include "RTClib.h"// time
#include <Adafruit_Sensor.h>// Humidity
#include <DHT.h>//Humidity
#include <DHT_U.h>//Humidity

// Digital pin connected to the DHT sensor
#define DHTPIN 2 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
#define DHTTYPE    DHT11     // DHT 11
//#define DHTTYPE    DHT22     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

// pin for the sd card
#define chipSelect 4

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;
RTC_DS1307 rtc;
Adafruit_BMP085 bmp;
// integers for the annemometer
int rotationCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button

// itegers to hold temperature measures
int temperature;
int minimum = 100;
int maximum = 0;
// integer to hold pressure
float pressure;
//int to hold humidity
int humidity;
bool daytime = true;
void setup() {
  //error pin
  pinMode(3,OUTPUT);
  
  Serial.begin(9600);
  //begin rtc
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    //find the error
    while (1){analogWrite(3,50);}
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
  
  // begin sd card
  while (!Serial) {
    Serial.print("....."); // wait for serial port to connect. Needed for native USB port only
  }
  Serial.print("Initializing SD card...");

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1){analogWrite(3,50);}
  }
  Serial.println("card initialized.");

  // Begin pressure reading

  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {analogWrite(3,50);}
  }
  // begin DHT 
  
  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;

}

void loop() {
  Serial.println(analogRead(A0));
  Bmp();
  Humidity();
  if(analogRead(A0)<500){
    daytime = true;
  }
  if (daytime = true){
    if(analogRead(A0)>500){
      daytime = false;
      Write();
  }
  }

  delay(900000);
}


void Bmp() {
  // read Temperature from BMP is more acurate then DHT
  Serial.print("Temperature = ");
  temperature = bmp.readTemperature();
  Serial.print(temperature);
  Serial.println(" *C");
  
  if (temperature > maximum) {
    maximum = temperature;
  }
  if (temperature < minimum) {
    minimum = temperature;
  }

  // Read pressure from BMP
//  Serial.print("Pressure = ");
Serial.print(bmp.readPressure());
//  Serial.println(" Pa");
  pressure = bmp.readPressure();
  Serial.println(pressure);
}

void Humidity(){
  // Read humidity from DHT
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
    humidity = event.relative_humidity;
    Serial.print(humidity);
    Serial.println(F("%"));
}

void Write() {
  // make a string for assembling the data to log:
  
  String dataString = "";

  DateTime time = rtc.now();
  dataString = time.timestamp(DateTime::TIMESTAMP_FULL);
  dataString += ",";
  dataString += temperature;
  dataString += ",";
  dataString += minimum;
  dataString += ",";
  dataString += maximum;
  dataString += ",";
  dataString += pressure;
  dataString += ",";
  dataString += humidity;
  minimum = 99;
  maximum = 0;
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
  }
}
