/*  
title: "Code for to measure irradiance, humidity and temperature"
author: "Babur Erdem"
date: "2024-08-02"
update date: "2024-08-02"

* (ML8511 UV Sensor Read, by Nathan Seidle, from https://learn.sparkfun.com/tutorials/ml8511-uv-sensor-hookup-guide/ )
*/

#include <Wire.h>
#include <Adafruit_TSL2561_U.h>
#include <DHT.h>

// TSL2561 sensor settings
Adafruit_TSL2561_Unified tsl2561 = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);

// DHT sensor settings
#define DHTPIN 2          
#define DHTTYPE DHT22     
DHT dht(DHTPIN, DHTTYPE); 

// ML8511 sensor settings
int UVOUT = A0; 
int REF_3V3 = A1; 

void setup()
{
  Serial.begin(9600); 
  
  Wire.begin(); 
  // Initialize TSL2561
  if (!tsl2561.begin()) {
    Serial.print("Couldn't find TSL2561");
    while (1); // Halt the program
  }
  Serial.println("TSL2561 found"); 

  // Configure the TSL2561
  tsl2561.setGain(TSL2561_GAIN_16X);  // Set high gain (16x)
  tsl2561.setIntegrationTime(TSL2561_INTEGRATIONTIME_101MS);  // Set integration time to 101ms

  // Initialize ML8511 sensor
  pinMode(UVOUT, INPUT); 
  pinMode(REF_3V3, INPUT); 
  Serial.println("ML8511 ready"); 

  // Initialize DHT sensor
  dht.begin(); 
}

void loop()
{
  // Read TSL2561 sensor
  uint16_t broadband, ir;
  tsl2561.getLuminosity(&broadband, &ir); 

  // Calculate irradiance for TSL2561
  double irrBroadband = (double)broadband / 27.5; // µW/cm² for 640 nm, high gain, 101 ms
  double irrIr = (double)ir / 6.9; // µW/cm² for 940 nm, high gain, 101 ms

  // Read ML8511 sensor
  int uvLevel = averageAnalogRead(UVOUT); 
  int refLevel = averageAnalogRead(REF_3V3); 

  // Calculate irradiance for TSL2561
  double outputVoltage = 3.3 / refLevel * uvLevel; 
  double uvIntensity = mapfloat(outputVoltage, 0.99, 2.8, 0.0, 15.0); // mW/cm²
  uvIntensity *= 1000; // Convert to µW/cm²

  // Read DHT22 sensor
  float humidity = dht.readHumidity(); 
  float temperature = dht.readTemperature(); 

  // Print TSL2561 readings
  Serial.print("TSL2561 - Broadband: "); Serial.print(broadband);
  Serial.print(" | IR: "); Serial.print(ir);
  Serial.print(" | Irradiance (Broadband): "); Serial.print(irrBroadband, 3); Serial.print(" µW/cm²");
  Serial.print(" | Irradiance (IR): "); Serial.print(irrIr, 3); Serial.println(" µW/cm²");

  // Print ML8511 readings
  Serial.print("ML8511 - Reference: "); Serial.print(refLevel);
  Serial.print(" | Output: "); Serial.print(uvLevel);
  Serial.print(" | Voltage: "); Serial.print(outputVoltage);
  Serial.print(" | Irradiance (UV): "); Serial.print(uvIntensity, 3); Serial.println(" µW/cm²");

  // Print DHT22 readings
  Serial.print("DHT22 - Humidity: "); Serial.print(humidity);
  Serial.print(" % | Temperature: "); Serial.print(temperature);
  Serial.println(" °C");

  Serial.println();

  delay(10000); 
}

// Takes averaged value for ML8511
int averageAnalogRead(int pinToRead)
{
  byte numberOfReadings = 8; // Number of readings to average
  unsigned int runningValue = 0; 
  
  for(int x = 0 ; x < numberOfReadings ; x++)
    runningValue += analogRead(pinToRead); // Read the pin and add to running value
  runningValue /= numberOfReadings; // Calculate the average

  return(runningValue);  
}

// Map function for floating point values
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
