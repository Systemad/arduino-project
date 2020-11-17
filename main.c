#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

#include "lcd.h"
#include "helpers.h"
#include "dht.h"
#include "serial.h"

void main(void)
{   
    char buffer[50];
    int8_t temperature = 0;
    uint8_t firstLine[] = " Temp: ";
    uint8_t celsius[] = " C";
    char degreeSymbol = (char)223;
    uint8_t secondLine[] = " Hum: ";
    
    lcd_init();
    uart_init();

    GREEN_OUTPUT();
    YELLOW_OUTPUT();
    RED_OUTPUT();


    while (1)
    {
        lcd_instruct(LCD_SetCursor | LCD_LINE_ONE);
        lcd_sendString(firstLine);
        temperature = dht_getdata(temperature);
		itoa(temperature, buffer, 10);
        lcd_sendString(buffer);
        lcd_sendChar(degreeSymbol);
        lcd_sendString(celsius);

        lcd_instruct(LCD_SetCursor | LCD_LINE_TWO);
        lcd_sendString(secondLine);

		_delay_ms(1000);

        /*
        if(temperature >= 26){
            RED_TOGGLE();
        }
        else if (temperature >= 26) {
            YELLOW_TOGGLE();
        }
        else {
            GREEN_TOGGLE();
        }
        */

    }
}
