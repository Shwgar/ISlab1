#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"

void main (void) {
  char namn[] = "Martin\n";
  uart_init();
  while (1) {
    //uart_putchar('c');
    uart_putstr(namn);
    _delay_ms(1000);
  }
}
