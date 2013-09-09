/*
This a simple serial port thermometer application using the Thermocouple Nanoshield.
 
 Copyright (c) 2013 Circuitar
 This software is released under the MIT license. See the attached LICENSE file for details.
 */
#include <SPI.h>
#include "Nanoshield_Thermocouple.h"

Nanoshield_Thermocouple thermocouple;

void setup()
{
  Serial.begin(115200);
  Serial.println("-------------------------------");
  Serial.println(" Nanoshield Serial Thermometer");
  Serial.println("-------------------------------");
  Serial.println("");

  // Initialize thermocouple
  thermocouple.begin();
}

void loop()
{
  // Read thermocouple data
  thermocouple.read();

  // Print temperature in the serial port, checking for errors
  if (thermocouple.isShortedToVcc()) {
    Serial.println("Shorted to VCC");
  } 
  else if (thermocouple.isShortedToGnd()) {
    Serial.println("Shorted to GND");
  } 
  else if (thermocouple.isOpen()) {
    Serial.println("Open circuit");
  } 
  else {
    Serial.print(thermocouple.getExternal());
    Serial.print(", ");
    Serial.println(thermocouple.getInternal());
  }

  // Wait for next second
  delay(1000);
}


