#ifndef SERIAL_H_
#define SERIAL_H_

void uart_init(void);

static void uart_putchar(char chr);
void uart_putstr(const char *str);

static char uart_getchar(void);

static void uart_echo(void);

void uart_blink(void);

#endif
