#define FOSC 16000000
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "serial.h"

void uart_init(void){
  unsigned int ubrr = MYUBRR;
  UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

void uart_putchar(char chr){
  while ( !( UCSR0A & (1<<UDRE0)) );
  if (chr == '\n') {
    UDR0 = chr;
    uart_putchar('\r');
  }
  else{
    UDR0 = chr;
  }
}
void uart_putstr(const char *str){
    int length = strlen(str);
  for (int i = 0; i < length; i++) {
      uart_putchar(str[i]);
  }
}

char uart_getchar(void){
  while (!(UCSR0A & (1<<RXC0))) {
  }
  return UDR0;
}

void uart_echo(void){
  char send;
  send = uart_getchar();
  if (send == '\r') {
    uart_putchar('\n');
  }
  else{
    uart_putchar(send);
  }
}
