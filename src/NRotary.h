#ifndef NRotary_h
#define NRotary_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <NDefs.h>

enum ROTARYSTATES
{
	IDLE,
	COUNTER_CLOCKWISE,
	CLOCKWISE
};

class Rotary
{
public:
	Rotary();
	Rotary(byte, byte, bool, bool, unsigned int);
	Rotary(byte, byte, byte, bool, bool, unsigned int);
	void serviceRoutine();
	int getState();
	bool getSwitch();
	mutable int mode;
private:
	void init();
	void defineMode();
	const byte pinA;
	const byte pinB;
	const byte pinS;
	const unsigned int debouce;
	const bool inverted;
	const bool useInterrupt;
	int state;
	unsigned long lastRead;
};
#endif