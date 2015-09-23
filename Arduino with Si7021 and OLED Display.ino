/******************************************************************************
OLEd Si7021 Humidity/Temperature Display using U8GLIB Library

visit https://code.google.com/p/u8glib/ for full details of the U8GLIB library and
full instructions for use.

by Chris Rouse Oct 2015

Using a IIC 128x64 OLED with SSD1306 chip
 
Si7021 Humidity/Temperature Sensor

Wire OLED:
  VCC +5v
  GND GND
  SDA Analog pin 4
  SCL Analog pin 5
Wire Si7021
This is a 3v device and although the board has a 3v reulator
the I2C connections may need a logic level convertor
  Vcc to Arduino 5 volts
  Gnd to Arduino Gnd
  SDA to Arduino pin A4 via logic level convertor
  SCL to Arduino pin A5 via logic level convertor

******************************************************************************/

// Add libraries
  #include "U8glib.h"
  #include <SPI.h>
  #include <Wire.h>
  #include <SI7021.h>  
  
// setup u8g object
  U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);	// I2C 
//
  SI7021 sensor;
//
  int humidity;
  double temperature;
  String thisTemp = "";
  String thisHumidity = "";
//

void draw(void) {
  u8g.setFont(u8g_font_profont12);
  u8g.drawStr(25,10, "Si7021 Sensor");
  u8g.setFont(u8g_font_profont12); 
  thisTemp = String(temperature) + "\260C";
  const char* newTempC = (const char*) thisTemp.c_str();
  u8g.drawStr(65,25, newTempC);
 // now display Humidity
  u8g.setFont(u8g_font_profont29); 
  thisHumidity = String(humidity) + "%";
  const char* newHumidity = (const char*) thisHumidity.c_str();
  u8g.drawStr(15,50, newHumidity);  
  u8g.setFont(u8g_font_profont12);
  u8g.drawStr(65,50, "humidity");  
}

void setup(void) {
  Serial.begin(9600);
  Wire.begin();
  Serial.println("Checking I2C Devices");
  sensor.begin(); 
  if(sensor.getDeviceId() == 20 || sensor.getDeviceId() == 21){
    Serial.print("Si70");
    Serial.print(sensor.getDeviceId()); 
    Serial.println(" is present");
    Serial.println("OK");
  }
  else{
  Serial.println("Device not present");
  while(1); // dont do anything
  }
}

void loop(void) {
  humidity = sensor.getHumidityPercent();
  temperature = sensor.getCelsiusHundredths();
  temperature = temperature/100;
  // picture loop
  u8g.firstPage();  
  do {
    draw();
  } while( u8g.nextPage() );
  // rebuild the picture after some delay
  delay(50);
}

