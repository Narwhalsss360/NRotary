#include "NRotary.h"

Rotary::Rotary()
	:pinA(NULL), pinB(NULL), pinS(NULL), inverted(NULL), useInterrupt(NULL), debouce(NULL), lastRead(ZERO)
{

}

/// <summary>
/// Rotary Class.
/// </summary>
/// <param name="_pinA">Rotary pin A</param>
/// <param name="_pinB">Rotary pin B</param>
Rotary::Rotary(byte _pinA, byte _pinB, bool useI, bool _inverted, unsigned int _debouce)
	:pinA(_pinA), pinB(_pinB), pinS(NULL), inverted(_inverted), useInterrupt(useI), debouce(_debouce), lastRead(ZERO)
{
	this->init();
}

/// <summary>
/// Rotary Class
/// </summary>
/// <param name="_pinA">Rotary pin A</param>
/// <param name="_pinB">Rotary pin B</param>
/// <param name="_pinS">Rotary pin Switch</param>
Rotary::Rotary(byte _pinA, byte _pinB, byte _pinS, bool useI, bool _inverted, unsigned int _debouce)
	:pinA(_pinA), pinB(_pinB), pinS(_pinS), inverted(_inverted), useInterrupt(useI), debouce(_debouce), lastRead(ZERO)
{
	this->init();
}

void Rotary::init()
{
	pinMode(this->pinA, (this->inverted) ? INPUT_PULLUP: INPUT);
	pinMode(this->pinB, (this->inverted) ? INPUT_PULLUP : INPUT);
	pinMode(this->pinS, (this->inverted) ? INPUT_PULLUP : INPUT);
	this->defineMode();
}

void Rotary::serviceRoutine()
{
	if (!(this->inverted) ? !digitalRead(this->pinA) : digitalRead(this->pinA))
		return;
	if (this->useInterrupt)
	{
		if (millis() - this->lastRead >= this->debouce)
		{
			this->lastRead = millis();
			if ((this->inverted) ? !digitalRead(this->pinB) : digitalRead(this->pinB))
			{
				this->state = COUNTER_CLOCKWISE;
			}
			else
			{
				this->state = CLOCKWISE;
			}
		}
	}
}

bool Rotary::getSwitch()
{
	if (this->pinS != NULL)
	{
		return (this->inverted) ? !digitalRead(this->pinS) : digitalRead(this->pinS);
	}
	else
	{
		return false;
	}
}

int Rotary::getState()
{
	if (!this->useInterrupt)
	{
		bool pinA = (this->inverted) ? !digitalRead(this->pinA) : digitalRead(this->pinA);
		bool pinB = (this->inverted) ? !digitalRead(this->pinB) : digitalRead(this->pinB);

		if (pinA != pinB)
		{
			if (pinB)
			{
				return COUNTER_CLOCKWISE;
			}
			else
			{
				return CLOCKWISE;
			}
		}
		else
		{
			return IDLE;
		}
	}
	else
	{
		int returnState = state;
		this->state = IDLE;
		return returnState;
	}
}

void Rotary::defineMode()
{
	this->mode = (this->inverted) ? FALLING : RISING;
}