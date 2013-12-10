/*
 Read temperatures from multiple Thermocouple Nanoshields.
 
 Copyright (c) 2013 Circuitar
 This software is released under the MIT license. See the attached LICENSE file for details.
 */
#include <SPI.h>
#include "Nanoshield_Thermocouple.h"

// Use 6 thermocouples simultaneously
#define THERMOCOUPLES 4

// Create an array of thermocouples
Nanoshield_Thermocouple thermocouple[THERMOCOUPLES];

// Define the CS pin for each thermocouple
int cs[] = { 6, 7, 8, 9 };

void setup()
{
  Serial.begin(115200);
  Serial.println("------------------");
  Serial.println(" MultiThermometer");
  Serial.println("------------------");
  Serial.println("");

  // Initialize each Thermocouple Nanoshield, selecting the corresponding CS pin
  for(int i = 0; i < THERMOCOUPLES; i++) {
    thermocouple[i].begin(cs[i]);
  }
}

void loop()
{
  for(int i = 0; i < THERMOCOUPLES; i++) {
    // Read thermocouple data
    thermocouple[i].read();
    
    // Print thermocouple number
    Serial.print(i + 1);
    Serial.print(": ");
  
    // Print temperature in the serial port, checking for errors
    if (thermocouple[i].isShortedToVcc()) {
      Serial.println("Shorted to VCC");
    } 
    else if (thermocouple[i].isShortedToGnd()) {
      Serial.println("Shorted to GND");
    } 
    else if (thermocouple[i].isOpen()) {
      Serial.println("Open circuit");
    } 
    else {
      Serial.print(thermocouple[i].getExternal());
      Serial.print(", ");
      Serial.println(thermocouple[i].getInternal());
    }
  }

  // Wait for next second
  delay(1000);
}
