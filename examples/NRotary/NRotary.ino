#include <NRotary.h>

#define BAUDRATE 115200
#define ROTARY_A_PIN 2
#define ROTARY_B_PIN 3
#define ROTARY_MODE INPUT_PULLUP
#define ROTARY_PIN_INVERTED false

RotaryDecoder decoder = RotaryDecoder(ROTARY_A_PIN, ROTARY_B_PIN, ROTARY_MODE, ROTARY_PIN_INVERTED);

void rotaryISR()
{
    rotary_state_t state = decoder.decode();
    if (!ROTARY_TURNED_STATE(state)) //No CCW or CW
        return;

    Serial.println(state == CCW ? "Counter-Clockwise" : "Clockwise");
}

void setup()
{
    Serial.begin(BAUDRATE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_A_PIN), rotaryISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_B_PIN), rotaryISR, CHANGE);
}

void loop()
{

}
