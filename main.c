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

    lcd_init();
	uart_init();
	led_init();

    while (1)
    {	
		temperature = dht_getdata(temperature);
		itoa(temperature, buffer, 10);
		led_state(temperature);
		
		// Write temperature to LCD directly on line 2 
		lcd_instruct(LCD_SetCursor | LCD_LINE_TWO);
		lcd_sendString(firstLine);
        lcd_sendString(buffer);
        lcd_sendChar(degreeSymbol);
        lcd_sendString(celsius);
		_delay_ms(1000);
	}
}