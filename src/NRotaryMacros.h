#define __ROTARY_TIME_F__() millis()
#define ROTARY_ISR_MODE(pm) ((pm == INPUT_PULLUP) ? FALLING : RISING )