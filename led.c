#include <avr/io.h>
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
	LED_GREEN_DDR |= _BV(LED_GREEN_BIT);
	LED_RED_DDR |= _BV(LED_RED_BIT);
	LED_YELLOW_DDR |= _BV(LED_RED_BIT);
}
void warning(char buff){
	
	// Only turn on Yellow
	GREEN_OFF();
	RED_OFF();
	YELLOW_ON();

	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(warning_mode);
}

void critical(char buff){
	// Only turn on red
	YELLOW_OFF();
	GREEN_OFF();
	RED_ON();

	// Send current mode to 1st line of Display
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(critical_mode);
}

void ok(char buff){
	// Only turn on green
	YELLOW_OFF();
	RED_OFF();
	GREEN_ON();
	
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
	if (temp <= 19)
	{
	    if (temp <= 15)
	    {
			critical();
	    } else {
			warning();
	    }
	} else {
	    ok();
	}
	*/
	
	if (temp >= 22)
	{
	    if (temp >= 27)
	    {
			critical(buffer);
	    } else {
			warning(buffer);
	    }
	} else {
	    ok(buffer);
	}

	// send temperature to 2nd line
	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(temperature);
	lcd_sendString(buffer);
	lcd_sendString(celsius);

}