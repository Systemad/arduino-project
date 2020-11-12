#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "helpers.h"
#include "dht.h"
#include "serial.h"

void main(void)
{   
    char buffer[50];
    int8_t temperature = 0;
    
    uart_init();

    GREEN_OUTPUT();
    YELLOW_OUTPUT();
    RED_OUTPUT();

    while (1)
    {
        temperature = dht_getdata(temperature);
		itoa(temperature, buffer, 10);
		uart_putstr("temperature: ");
		uart_putstr(buffer);
		uart_putstr("C");
		uart_putstr("\r\n");
		_delay_ms(2000);
        /*
        RED_TOGGLE();
        YELLOW_TOGGLE();
        GREEN_TOGGLE();
        _delay_ms(1000);
        */
    }
}
