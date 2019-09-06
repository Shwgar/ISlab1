#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "blink.h"

void main (void) {
  uart_init();
  DDRB |= 1<<DDB0;
  while (1) {
    uart_blink();
  }
}
