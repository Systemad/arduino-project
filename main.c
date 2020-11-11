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
	char printbuff[100];

	//init uart
	uart_init();

	//init interrupt
	//sei();

	int8_t temperature = 0;
	int8_t humidity = 0;

	while(1) {
		if(dht_gettemperaturehumidity(&temperature, &humidity) != -1) {
			itoa(temperature, printbuff, 10);
			uart_putstr("temperature: ");
			uart_putstr(printbuff);
			uart_putstr("C");
			uart_putstr("\r\n");

			/*
			itoa(humidity, printbuff, 10);
			uart_putstr("humidity: ");
			uart_putstr(printbuff);
			uart_putstr("%RH");
			uart_putstr("\r\n");
			*/
		} else {
			uart_putstr("error");
			uart_putstr("\r\n");
		}
		uart_putstr("\r\n");
		_delay_ms(2000);
	}
	
	return 0;
}
