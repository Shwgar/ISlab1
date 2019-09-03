#include <avr/io.h>
#include <util/delay.h>
#include "serial.h"
#include "blink.h"

int main(void) {
  DDRB |= 1<<DDB0;
  while(1){
  blink();
  }
}
