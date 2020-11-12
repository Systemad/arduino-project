#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "dht.h"
#define F_CPU 16000000UL

#include "serial.h"

int main(void)
{
	char buffer[50];

	//init uart
	uart_init();

	//init interrupt
	//sei();

	int8_t temperature = 0;

	while(1) {
		temperature = dht_getdata(temperature);
		itoa(temperature, buffer, 10);
		uart_putstr("temperature: ");
		uart_putstr(buffer);
		uart_putstr("C");
		uart_putstr("\r\n");
		_delay_ms(2000);
	}
	
	return 0;
}
