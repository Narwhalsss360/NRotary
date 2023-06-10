#include "RotaryDecoder.h"

#define CW 0b00001000
#define CCW 0b00010000

#define CCW_STATE_OFFSET 3

#define INVERTABLE(i_cond, expr) ((i_cond) ? !expr : expr)

const byte nextTimeState[7][4] =
{
	{ 0, 1, 1 + CCW_STATE_OFFSET, 0 },
	{ 2, 1, 0, 0 },
	{ 2, 1, 3, 0 },
	{ 2, 0, 3, CW },

	{ 2 + CCW_STATE_OFFSET, 0, 1 + CCW_STATE_OFFSET, 0 },
	{ 2 + CCW_STATE_OFFSET, 3 + CCW_STATE_OFFSET, 1 + CCW_STATE_OFFSET, 0 },
	{ 2 + CCW_STATE_OFFSET, 3 + CCW_STATE_OFFSET, 0, CCW }
};

RotaryDecoder::RotaryDecoder(const byte pinA, const byte pinB, const byte mode, const bool inverted)
    : m_PinA(pinA), m_PinB(pinB), m_Timestate(0), m_Inverted(inverted)
{
    pinMode(pinA, mode);
    pinMode(pinB, mode);
}

byte RotaryDecoder::decode()
{
	if (m_Timestate >= CW) m_Timestate = 0;

	byte combination = (INVERTABLE(m_Inverted, digitalRead(m_PinA)) << 1 | INVERTABLE(m_Inverted, digitalRead(m_PinB)));
	m_Timestate = nextTimeState[m_Timestate][combination];
	return m_Timestate;
}

byte RotaryDecoder::timeState()
{
	return m_Timestate;
}
