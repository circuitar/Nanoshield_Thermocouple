/**
 * @file SimpleThermometer.ino
 * This a simple serial port thermometer application using the Thermocouple Nanoshield.
 * 
 * Copyright (c) 2013 Circuitar
 * This software is released under the MIT license. See the attached LICENSE file for details.
 */
#include <SPI.h>
#include "Nanoshield_Thermocouple.h"

Nanoshield_Thermocouple thermocouple;

void setup()
{
  Serial.begin(9600);
  Serial.println("-------------------------------");
  Serial.println(" Nanoshield Serial Thermometer");
  Serial.println("-------------------------------");
  Serial.println("");

  // Initialize the thermocouple
  // The CS pin can be passed as a parameter if different than pin D8,
  //  e.g. thermocouple.begin(7)
  thermocouple.begin();
}

void loop()
{
  // Read thermocouple data
  thermocouple.read();

  // Print temperature in the serial port, checking for errors
  Serial.print("Internal: ");
  Serial.print(thermocouple.getInternal());

  Serial.print(" | External: ");
  if (thermocouple.isShortedToVcc()) {
    Serial.println("Shorted to VCC");
  } else if (thermocouple.isShortedToGnd()) {
    Serial.println("Shorted to GND");
  } else if (thermocouple.isOpen()) {
    Serial.println("Open circuit");
  } else {
    Serial.println(thermocouple.getExternal());
  }

  // Wait for next second
  delay(1000);
}

