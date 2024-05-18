#include <NRotary.h>

#define BAUDRATE 115200
#define ROTARY_A_PIN 2
#define ROTARY_B_PIN 3
#define ROTARY_MODE INPUT_PULLUP
#define ROTARY_PIN_INVERTED false

RotaryDecoder decoder = RotaryDecoder(ROTARY_A_PIN, ROTARY_B_PIN, ROTARY_MODE, ROTARY_PIN_INVERTED);
Gradational gradational;

uint32_t value1 = 0;
uint32_t value1Low = 0;
uint32_t value1High = 10;
uint32_t value1Step = 1;

double value2 = 0;
double value2Low = 0;
double value2High = 1;
double value2Step = 0.01;

void rotaryISR()
{
    rotary_state_t state = decoder.decode();
    if (state < CW) //No CCW or CW
        return;
    if (state == CCW)
        gradational.gradate(DECREMENT);
    else
        gradational.gradate(INCREMENT);
}

void swap()
{
    if (gradational.current() == &value1)
    {
        gradational.set<double>(&value2, value2Low, value2High, value2Step, I_DOUBLE);
    }
    else
    {
        gradational.set<uint32_t>(&value1, value1Low, value1High, value1Step, I_U32);
    }
}

void serialEvent()
{
    while (Serial.available())
    {
        Serial.read();
        delayMicroseconds(500);
    }
    swap();
}

void setup()
{
    Serial.begin(BAUDRATE)
    attachInterrupt(digitalPinToInterrupt(ROTARY_A_PIN), rotaryISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_B_PIN), rotaryISR, CHANGE);
}

void loop()
{
    if (gradational.current() == &value1)
    {
        Serial.print("Value 1:");
        Serial.println(value1);
    }
    else
    {
        Serial.print("Value 2:");
        Serial.println(value2);
    }
}
