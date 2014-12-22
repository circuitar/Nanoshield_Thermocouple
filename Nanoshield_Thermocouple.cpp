/*
This is the library to access the Thermocouple Nanoshield

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#include "Nanoshield_Thermocouple.h"

Nanoshield_Thermocouple::Nanoshield_Thermocouple() {
	csPin = 8;
	intTemp = 0;
	extTemp = 0;
	shortToVcc = false;
	shortToGnd = false;
	openCircuit = false;
}

void Nanoshield_Thermocouple::begin(uint8_t cs)
{
	// Initialize SPI
	SPI.begin();
	
	// Set chip select pin as output and deselect the chip
	csPin = cs;
	digitalWrite(csPin, HIGH);
	pinMode(csPin, OUTPUT);
}

void Nanoshield_Thermocouple::read()
{
	uint32_t data = 0;
	uint16_t rawTemp = 0;

	// Select the chip
	digitalWrite(csPin, LOW);
	
	// Read and shift four bytes into the data variable
	for (int i = 0; i < 4; i++) {
		data = (data << 8) | SPI.transfer(0);
	}

	// Deselect the chip
	digitalWrite(csPin, HIGH);
	
	// Get 12-bit signed internal temperature from data
	rawTemp = (data & 0xFFF0) >> 4;
	if (rawTemp & 0x800) {
		// Negative temperature (two's complement)
		intTemp = -((4096 - rawTemp) * 0.0625);
	} else {
		// Positive temperature
		intTemp = rawTemp * 0.0625;
	}
	
	// Get 14-bit signed external temperature from data
	rawTemp = (data & 0xFFFC0000) >> 18;
	if (rawTemp & 0x2000) {
		// Negative temperature (two's complement)
		extTemp = -((16384 - rawTemp) * 0.25);
	} else {
		// Positive temperature
		extTemp = rawTemp * 0.25;
	}
	
	// Get errors from data
	shortToVcc = data & 0b100;
	shortToGnd = data & 0b010;
	openCircuit = data & 0b001;
}

double Nanoshield_Thermocouple::getInternal()
{
	return intTemp;
}

double Nanoshield_Thermocouple::getExternal()
{
	return extTemp;
}

bool Nanoshield_Thermocouple::isShortedToVcc()
{
	return shortToVcc;
}

bool Nanoshield_Thermocouple::isShortedToGnd()
{
	return shortToGnd;
}

bool Nanoshield_Thermocouple::isOpen()
{
	return openCircuit;
}

bool Nanoshield_Thermocouple::hasError()
{
	return shortToVcc || shortToGnd || openCircuit;
}
