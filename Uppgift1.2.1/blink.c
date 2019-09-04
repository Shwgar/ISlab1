#include <avr/io.h>
#include <util/delay.h>
#include "blink.h"

void blink(void){
    PORTB ^= 1<<PORTB0;
    _delay_ms(500);
}
