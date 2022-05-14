#include <NRotary.h>

//Serial.begin() rate
int baudrate = 9600;

//Rotary encoder pin A.
int rotaryAPin = 2;

//Rotary encoder pin B.
int rotaryBPin = 4;

//Rotary encoder pin S (Button).
int rotarySPin = 3;

//Debounce time.
int debounce = 50;

//Using interrupts (Recommended).
bool usingInterrupt = true;

Rotary rotary = Rotary(rotaryAPin, rotaryBPin, rotarySPin, usingInterrupt, INPUT_PULLUP, debounce);
//                         ^            ^           ^            ^              ^           ^
//                       pin A        pin B       pin S       usingISR     pull up/down debounce time

//Where to save rotary turning state.
int rotaryState = IDLE;

//Where to save rotary switch state.
bool rotarySwitch = false;

//Interrupt Service Routine(ISR).
void rotaryServiceRoutineWrapper()
{
    //Run rotary.serviceRoutine() here.
    rotary.serviceRoutine();
}

void setup()
{
    Serial.begin(baudrate);
    attachInterrupt(digitalPinToInterrupt(rotaryAPin), rotaryServiceRoutineWrapper, rotary.mode);
    //                           ^                                  ^                   ^
    //                          Pin                                ISR                 mode
    //ISR mode is calculated for you in the constructor.
}

void loop()
{
    //Save the state of the rotary encoder. can only be called once per loop.
    rotaryState = rotary.getState();

    //Save the state of the rotary switch.
    rotarySwitch = rotary.getSwitch();

    //Returns true if not turning the rotary encoder.
    if (rotaryState == IDLE)
    {
        //Serial.println("Not turning...");
    }

    //Returns true if turning Counter-Clockwise. COUNTER_CLOCKWISE = 1.
    if (rotaryState == COUNTER_CLOCKWISE)
    {
        Serial.println("Turned Counter-Clockwise");
    }

    //Returns true if turning Clockwise. CLOCKWISE = 2.
    if (rotaryState == CLOCKWISE)
    {
        Serial.println("Turned Clockwise");
    }

    //Returns true if pressing the button.
    if (rotarySwitch == true)
    {
        Serial.println("Pressing Button");
    }
}