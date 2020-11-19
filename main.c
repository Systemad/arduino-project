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

uint8_t temp_text[] = " Temperature";
uint8_t celsius[] = " C";

void main(void)
{   

    led_init();
    lcd_init();
    uart_init();

	int8_t temperature = 0;
	char buffer[50];

    while (1)
    {	
		// Get temperature
		temperature = dht_getdata(temperature);
		
		// Convert to string and place in buffer
		itoa(temperature, buffer, 10);

		// send temperature to 2nd line
		lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
		lcd_sendString(temp_text);
		lcd_sendString(buffer);
		lcd_sendString(celsius);
		
		// Pass temperatire to function to check state and turn on LED
		led_state(temperature);
		_delay_ms(1000);
	}
}
