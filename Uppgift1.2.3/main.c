#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void main (void) {
  uart_init();
  while (1) {
    uart_echo();
  }
}
