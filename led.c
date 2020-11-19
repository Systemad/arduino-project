#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "dht.h"
#include "lcd.h"
#include "serial.h"

uint8_t temperature[] = " Temperature";
uint8_t ok_mode[] = " OK: ";
uint8_t warning_mode[] = " Warning: ";
uint8_t critical_mode[] = " Critical: ";
uint8_t celsius[] = " C";


void led_init(void) {
	//Sets LED pins to output initializing further usage:
	DDRB |= (1 << PB0); // Green
	DDRB |= (1 << PB1); // Yellow
	DDRB |= (1 << PB2); // Red
}

void warning(void){
	
	// Only turn on Yellow
	GREEN_OFF();
	RED_OFF();
	YELLOW_ON();

	uart_putstr(warning_mode);
	// Send current mode to 1st line of Display
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(warning_mode);
}

void critical(void){
	// Only turn on red
	YELLOW_OFF();
	GREEN_OFF();
	RED_ON();
	
	uart_putstr(critical_mode);
	// Send current mode to 1st line of Display
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(critical_mode);
}

void ok(void){
	// Only turn on green
	YELLOW_OFF();
	RED_OFF();
	GREEN_ON();

	uart_putstr(ok_mode);
	// Send current mode to 1st line of Display
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(ok_mode);
}

void led_state(int8_t temp) {

	// To write to LCD
	char buffer[50];
	itoa(temp, buffer, 10);

	//uart_putstr(buffer);
	/*
	if (temp <= 19 || temp >= 22)
	{
	    if (temp <= 15 || temp >= 27)
	    {
			critical();
	    } else {
			warning();
	    }
	} else {
	    ok();
	}
	_delay_ms(1000);
	*/
	
	
	if (temp <= 22 && temp >= 18){
		ok();
	}
	
	if (temp >= 27 || temp <= 15) {
		critical();
	}
	
	// send temperature to 2nd line
	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(temperature);
	lcd_sendString(buffer);
	lcd_sendString(celsius);

}