#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "led.h"
#include "lcd.h"
#include "dht.h"
#include "serial.h"

void main(void)
{   

    led_init();
    lcd_init();
    uart_init();

	int8_t temperature = 0;
	int8_t counter = 0;

    while (1)
    {	
		temperature = dht_getdata(temperature);
		//led_state(temperature);
		
		// Testing
		counter++;
        led_state(counter);
		_delay_ms(1000);
	}
}
