#ifndef NRotary_h
#define NRotary_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <NDefs.h>
#include "NRotaryMacros.h"
#include "NRotaryDeclarations.h"

Rotary::Rotary()
    : pinA(NULL), pinB(NULL), inverted(NULL), debounce(NULL), state(NULL), lastRead(NULL)
{
}

Rotary::Rotary(byte _pinA_, byte _pinB_, bool _inverted_, uint16_t _debounce_)
    : pinA(_pinA_), pinB(_pinB_), inverted(_inverted_), debounce(_debounce_), state(NULL), lastRead(NULL)
{
}

void Rotary::serviceRoutine()
{
    if (!((inverted) ? !digitalRead(pinA) : digitalRead(pinB))) return;
    if (__ROTARY_TIME_F__() - lastRead >= debounce)
    {
        lastRead = __ROTARY_TIME_F__();
        if((inverted) ? !digitalRead(pinB) : digitalRead(pinB))
        {
            state = COUNTER_CLOCKWISE;
        }
        else
        {
            state = CLOCKWISE;
        }
    }
}

uint8_t Rotary::getState()
{
    uint8_t returnState = state;
    state = IDLE;
    return returnState;
}

#endif