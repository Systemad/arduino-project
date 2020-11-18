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

uint8_t ok_mode[] = " OK: \r";
uint8_t warning_mode[] = " Warning: \r";
uint8_t critical_mode[] = " Critical: \r";

uint8_t celsius[] = " C";


void led_init(void) {
	//Sets LED pins to output initializing further usage:
	LED_GREEN_DDR |= _BV(LED_GREEN_BIT);
	LED_RED_DDR |= _BV(LED_RED_BIT);
	LED_YELLOW_DDR |= _BV(LED_RED_BIT);
}


void main(void)
{   
    char buffer[50];
    int8_t temperature = 0;
    uint8_t firstLine[] = " Temp: ";
    uint8_t celsius[] = " C";
    char degreeSymbol = (char)223;
    uint8_t secondLine[] = " Hum: ";

    int8_t counter;
    

    //led_init();
    lcd_init();
    uart_init();

    while (1)
    {

        DDRD |= (1<<PD6);

        PORTB |= (1 << PD6);
        _delay_ms(2000);
        PORTB &= ~(1 << PD6);
        //counter++;
        //uart_putstr(critical_mode1);
        //led_state(counter);
        //_delay_ms(2000)
    }
}



void led_state(int8_t temp) {

	// To write to LCD
	char buffer[100];
	itoa(temp, buffer, 10);

	if (temp >= 22 || temp <= 19 )
	{
	    if (temp >= 27 || (temp <= 15 )
	    {
		critical();
	    } else {
		warning();
	    }
	} else {
	    ok();
	}
}


void warning(char buff){
	// Only turn on Yellow
	//GREEN_OFF();
	//RED_OFF();
	//YELLOW_ON();
	
	uart_putstr(warning_mode);

	/*
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(warning_mode);

	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(buff);
	lcd_sendString(celsius);
	*/

}

void critical(char buff){
	// Only turn on red
	//YELLOW_OFF();
	//GREEN_OFF();
	//RED_ON();

	uart_putstr(critical_mode);

	/*
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(critical_mode);

	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(buff);
	lcd_sendString(celsius);
	*/
}

void ok(char buff){
	// Only turn on green
	//YELLOW_OFF();
	//RED_OFF();
	//GREEN_ON();

	uart_putstr(ok_mode);

	/*
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(ok_mode);

	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(buff);
	lcd_sendString(celsius);
	*/
}
