#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "lcd.h"
#include "dht.h"
#include "serial.h"
#include "led.h"

void main(void)
{   
    char buffer[50];
    int8_t temperature = 0;
    uint8_t firstLine[] = " Temp: ";
    uint8_t celsius[] = " C";
    char degreeSymbol = (char)223;
    
	uint8_t counter = 0;
    lcd_init();
	uart_init();
	led_init();

    while (1)
    {	
		counter++;

		led_state(counter);
		_delay_ms(1000);

		lcd_instruct(LCD_SetCursor | LCD_LINE_TWO);
		lcd_sendString(firstLine);
        temperature = dht_getdata(temperature);
		itoa(temperature, buffer, 10);
        lcd_sendString(buffer);
        lcd_sendChar(degreeSymbol);
        lcd_sendString(celsius);

		/*
        lcd_instruct(LCD_SetCursor | LCD_LINE_ONE);
        lcd_sendString(firstLine);
        temperature = dht_getdata(temperature);
		itoa(temperature, buffer, 10);
        lcd_sendString(buffer);
        lcd_sendChar(degreeSymbol);
        lcd_sendString(celsius);

        lcd_instruct(LCD_SetCursor | LCD_LINE_TWO);
        lcd_sendString(secondLine);
		uart_putstr(buffer);
		_delay_ms(2000);
		
		lcd_sendString(secondLine);
		
		_delay_ms(1000);
		*/
	}
}