#ifndef NDefs
#define NDefs

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define ZERO 0
#define NEWLINE '\n'
#define CARRIAGERETURN '\r'
#define NULLTERMINATOR '\0'

#ifdef ARDUINO_ARCH_AVR
#define ULONG_MAX 4294967295 
#define LONG_MAX 2147483647
#define LONG_MIN -2147483648

#define UINT_MAX 65535
#define INT_MAX 32767
#define INT_MIN -32768

#define BYTE_MAX 255

#define ADC_MAX 1023
#define PWN_MAX 255
#endif // ARDUINO_ARCH_AVR

#define SERIALCOM_BAUD 1000000

#define addInterrupt(pin, ISR, mode) attachInterrupt(digitalPinToInterrupt(pin), ISR, mode);
#define removeInterrupt(pin) detachInterrupt(digitalPinToInterrupt(pin));
#define BCD2DEC(num) hornerScheme(num, 0x10, 10)

#endif