#ifndef RotaryDecoder_h
#define RotaryDecoder_h

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define CW 0b00001000
#define CCW 0b00010000

#define ROTARY_TURNED_STATE(state) (state < CW)

using rotary_state_t = byte;

class RotaryDecoder
{
public:
    /// @brief Class for interpreting a rotary encoder
    /// @param pinA encoder pin A
    /// @param pinB encoder pin B
    /// @param mode `pinMode()` mode -> `INPUT` or `INPUT_PULLUP`
    /// @param inverted invert reading of pins (seperate from `mode`)
    RotaryDecoder(const byte pinA, const byte pinB, const byte mode, const bool inverted = false);

    /// @brief Interpret state of rotary from pin.
    /// @return `rotary_state_t` interpreted state state
    rotary_state_t decode();

    /// @brief Get the state of the rotary since last interpretation (interpreter: `decode()`).
    /// @return `rotary_state_t` current state
    rotary_state_t timeState();

private:
    const byte m_PinA, m_PinB;
    byte m_Timestate;
    bool m_Inverted;
};

#endif
