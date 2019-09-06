#include <avr/io.h>
#include <util/delay.h>
#include "blink.h"

void blink(int onoff){
    if (onoff) {
      PORTB |= 1<<PORTB0;
    }
    else if(!onoff){
      PORTB &= 0<<PORTB0;
    }
}
