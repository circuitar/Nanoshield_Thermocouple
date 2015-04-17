/*
 Read temperatures from multiple Thermocouple Nanoshields.
 
 Copyright (c) 2013 Circuitar
 This software is released under the MIT license. See the attached LICENSE file for details.
 */
#include <SPI.h>
#include "Nanoshield_Thermocouple.h"

// Define the CS pin for each thermocouple
byte cs[] = { 4, 7, 8, 10, A3 };

// Create an array of thermocouples
Nanoshield_Thermocouple thermocouple[sizeof(cs)];

void setup()
{
  Serial.begin(115200);
  Serial.println("------------------");
  Serial.println(" MultiThermometer");
  Serial.println("------------------");
  Serial.println("");

  // Initialize each Thermocouple Nanoshield, selecting the corresponding CS pin
  for(int i = 0; i < sizeof(cs); i++) {
    thermocouple[i].begin(cs[i]);
  }
}

void loop()
{
  for(int i = 0; i < sizeof(cs); i++) {
    // Read thermocouple data
    thermocouple[i].read();
    
    // Print thermocouple number
    Serial.print(i + 1);
    Serial.print(": ");
  
    // Print temperature in the serial port, checking for errors
    if (thermocouple[i].isShortedToVcc()) {
      Serial.print("Shorted to VCC");
    } else if (thermocouple[i].isShortedToGnd()) {
      Serial.print("Shorted to GND");
    } else if (thermocouple[i].isOpen()) {
      Serial.print("Open circuit");
    } else {
      Serial.print(thermocouple[i].getExternal());
    }
    Serial.print(", ");
    Serial.println(thermocouple[i].getInternal());
  }
  Serial.println();

  // Wait for next second
  delay(1000);
}