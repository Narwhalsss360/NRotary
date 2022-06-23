enum ROTARYSTATES
{
    IDLE,
    COUNTER_CLOCKWISE,
    CLOCKWISE
};

class Rotary
{
private:
    const byte pinA, pinB, inverted, state;
    const uint16_t debounce;
    uint8_t state;
    uint32_t lastRead;
public:
    inline Rotary();
    inline Rotary(byte, byte, bool, uint16_t);
    inline void serviceRoutine();
    inline uint8_t getState();
    inline ~Rotary();
};