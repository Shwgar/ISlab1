#define FOSC 16000000
#define BAUD 38400
#define MYUBRR FOSC/16/BAUD-1
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "serial.h"
#include "blink.h"

void uart_init(void){
  unsigned int ubrr = MYUBRR;
  UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (0<<USBS0)|(3<<UCSZ00);
}

static void uart_putchar(char chr){
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

static char uart_getchar(void){
  while (!(UCSR0A & (1<<RXC0))) {
  }
  return UDR0;
}

static void uart_echo(void){
  char send;
  send = uart_getchar();
  if (send == '\r') {
    uart_putchar('\n');
  }
  else{
    uart_putchar(send);
  }
}

void uart_blink(void){
    int checkmax = 0; //räknare för att vi inte skall få overflows
    char check[7]; //string där vi spar input från terminal
    char temp; //char där vi tar in senaste inslagna char från terminal
    while(checkmax < 6){ //så länge vi har färre än 6 chars från teminalen tar vi in fler
      temp = uart_getchar(); //spar char från teminalen
        if(temp == '\n'){ //om terminalen har tryckt enter kollar vi om strängen stämmer med on/off
        check[checkmax] = temp; //lägg till \r i stängen
        if(strncmp(check, "on\r\n", 4) == 0){ //jämför ingående sträng mot on
          blink(1); //starta lampan
          break;
        }
        else if(strncmp(check, "off\r\n", 5) == 0){ //jämför ingående sträng mot off
          blink(0); //släck lampan
          break;
        }
        break; //om ingen stämmer efter enter, starta om
      }
      check[checkmax] = temp; //lägger till char i stängen på platsen vi är på
      checkmax++; //ökar räknaren.
    }
}
