/*
This is the library to access the Thermocouple Nanoshield

Copyright (c) 2013 Circuitar
This software is released under the MIT license. See the attached LICENSE file for details.
*/

#ifndef NANOSHIELD_THERMOCOUPLE_h
#define NANOSHIELD_THERMOCOUPLE_h

#include "Arduino.h"

class Nanoshield_Thermocouple {
	public:
		Nanoshield_Thermocouple();
		void begin(uint8_t cs = 8);
		void read();
		double getInternal();
		double getExternal();
		bool isShortedToVcc();
		bool isShortedToGnd();
		bool isOpen();
		bool hasError();

	protected:
		uint8_t csPin;
		double intTemp;
		double extTemp;
		bool shortToVcc;
		bool shortToGnd;
		bool openCircuit;
};

#endif