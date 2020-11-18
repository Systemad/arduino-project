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
    char buffer[50];
    int8_t temperature = 0;
    uint8_t firstLine[] = " Temp: ";
    uint8_t celsius[] = " C";
    char degreeSymbol = (char)223;
    uint8_t secondLine[] = " Hum: ";
    
    led_init();
    lcd_init();
    uart_init();

    while (1)
    {
        /*
        lcd_instruct(LCD_SetPosition | LCD_LINE_ONE);       //Sets the position on the first line
        lcd_sendString(firstLine);           
        temperature = dht_getdata(temperature);             //Receives data from the DHT11 and allocates it in the temp variable
		itoa(temperature, buffer, 10);                      //Non standard function that converts and int to a string 
        lcd_sendString(buffer);
        lcd_sendChar(degreeSymbol);
        lcd_sendString(celsius);

        lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);       //Start of the second line
        lcd_sendString(secondLine);

		_delay_ms(1000);

        led_state(temperature);                             //Meanwhile the state function is monitoring and adapting the LED accordingly
        */
        GREEN_TOGGLE();
        _delay_ms(1000);
        RED_TOGGLE();
        _delay_ms(1000);
        YELLOW_TOGGLE(); 
        _delay_ms(1000);
    }
}
