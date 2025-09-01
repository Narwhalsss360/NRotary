#include <NRotary.h>

#define BAUDRATE 115200
#define ROTARY_A_PIN 2
#define ROTARY_B_PIN 3
#define ROTARY_MODE INPUT_PULLUP
#define ROTARY_PIN_INVERTED false

RotaryDecoder decoder = RotaryDecoder(ROTARY_A_PIN, ROTARY_B_PIN, ROTARY_MODE, ROTARY_PIN_INVERTED);

uint32_t value1Initial = 0;
uint32_t value1Low = 0;
uint32_t value1High = 10;
uint32_t value1Step = 1;
Gradational<uint32_t> value1Gradational = Gradational<uint32_t>(value1Initial, value1Low, value1High, value1Step);

double value2Initial = 0;
double value2Low = 0;
double value2High = 1;
double value2Step = 0.01;
Gradational<double> value2Gradational = Gradational<double>(value2Initial, value2Low, value2High, value2Step);

AnyGradational* gradational = &value1Gradational;

void rotaryISR()
{
    rotary_state_t state = decoder.decode();
    if (state < CW) //No CCW or CW
        return;
    if (state == CCW)
        gradational->gradate(DECREMENT);
    else
        gradational->gradate(INCREMENT);
}

void swap()
{
    if (gradational == &value1Gradational)
    {
        gradational = &value1Gradational;
    }
    else
    {
        gradational = &value2Gradational;
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
    Serial.begin(BAUDRATE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_A_PIN), rotaryISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ROTARY_B_PIN), rotaryISR, CHANGE);
}

void loop()
{
    if (gradational == &value1Gradational)
    {
        Serial.print("Value 1:");
        Serial.println(value1Gradational.current());
    }
    else
    {
        Serial.print("Value 2:");
        Serial.println(value2Gradational.current());
    }
}
