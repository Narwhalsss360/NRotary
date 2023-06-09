#ifndef RotaryDecoder_h
#define RotaryDecoder_h

#include <Arduino.h>

class RotaryDecoder
{
public:
    RotaryDecoder(const byte pinA, const byte pinB, const byte mode, const bool inverted = false);

    byte decode();

    byte timeState();

private:
    const byte m_PinA, m_PinB;
    byte m_Timestate;
    bool m_Inverted;
};

#endif