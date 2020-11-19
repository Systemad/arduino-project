#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "dht.h"
#include "lcd.h"
#include "serial.h"

uint8_t ok_mode[] = " OK: ";
uint8_t warning_mode[] = " Warning: ";
uint8_t critical_mode[] = " Critical: ";


void led_init(void) {
	//Sets LED pins to output initializing further usage:
	DDRB |= (1 << PB5); // Green
	DDRB |= (1 << PB1); // Yellow
	DDRB |= (1 << PB2); // Red
}

void warning(void){
	
	// Only turn on Yellow
	YELLOW_ON();
	_delay_ms(500);
	GREEN_OFF();
	RED_OFF();

	// Send current mode to 1st line of Display
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(warning_mode);
}

void critical(void){
	// Only turn on red
	RED_ON();
	YELLOW_OFF();
	GREEN_OFF();
	
	// Send current mode to 1st line of Display
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(critical_mode);
}

void ok(void){
	// Only turn on green
	GREEN_ON();
	YELLOW_OFF();
	RED_OFF();

	// Send current mode to 1st line of Display
	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(ok_mode);
}

void led_state(int8_t temp) {
	if (temp <= MIN_TEMP){
		critical();
	}

	if (temp > 15 && temp <= 18) {
		warning();
	}

	if (temp > 18 && temp <= 23){
		ok();
	}

	if (temp > 23 && temp < 27){
		warning();
	}
	
	if (temp >= MAX_TEMP) {
		critical();
	}
}