#ifndef RotaryDecoder_h
#define RotaryDecoder_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define CW 0b00001000
#define CCW 0b00010000

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