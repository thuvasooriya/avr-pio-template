#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16 mhz clock speed
#define BAUD 115200
#define MYUBRR F_CPU / 16 / BAUD - 1

void USART_Init(unsigned int ubrr) {
  /* set baud rate */
  UBRR0H = (unsigned char)(ubrr >> 8);
  UBRR0L = (unsigned char)ubrr;
  /* enable receiver and transmitter */
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  /* set frame format: 8data, 2stop bit */
  UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void USART_Transmit(unsigned char data) {
  /* wait for empty transmit buffer */
  while (!(UCSR0A & (1 << UDRE0)))
    ;
  /* put data into buffer, sends the data */
  UDR0 = data;
}

void USART_Transmit_String(char *data) {
  while (*data != 0x00) {
    USART_Transmit(*data);
    data++;
  }
}

int main(void) {
  USART_Init(MYUBRR);

  /* test avr libc availability */
  char buffer[50];
  snprintf(buffer, sizeof(buffer), "avr libc is available!\r\n");
  USART_Transmit_String(buffer);

  /* test avr/io.h availability */
  DDRB |= (1 << DDB5); // Set pin 13 (LED) as output

  while (1) {
    /* blink led to show the program is running */
    PORTB |= (1 << PORTB5);  // Turn the LED on
    _delay_ms(500);          // Wait for 1 second
    PORTB &= ~(1 << PORTB5); // Turn the LED off
    _delay_ms(500);          // Wait for 1 second

    USART_Transmit_String("avr is running...\r\n");
  }

  return 0;
}
