#include <avr/io.h>
#include "led.h"
#include "dht.h"
#include "lcd.h"

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

void led_state(uint8_t temp) {

	// To write to LCD
	char buffer[100];
	itoa(temp, buffer, 10);

	if (temp >= MAX_TEMP - WARNING_DEFICIT){
		warning();
	} else if (temp >= MAX_TEMP){
		critical();
	}
	
	if (temp >= MIN_TEMP - WARNING_DEFICIT){
		warning();
	} else if (temp <= MIN_TEMP){
		critical();
	}
	else {
		ok();
	};
}


void warning(){
	GREEN_OFF();
	RED_OFF();
	YELLOW_ON();

	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(warning_mode);

	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(buffer);
	lcd_sendString(celsius);

}

void critical(){
	YELLOW_OFF();
	GREEN_OFF();
	
	RED_ON();

	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(critical_mode);

	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(buffer);
	lcd_sendString(celsius);
}

void ok(){
	// Turn off other LEDS
	YELLOW_OFF();
	RED_OFF();

	GREEN_ON();

	lcd_instruct(LCD_SetPosition | LCD_LINE_ONE); 
	lcd_sendString(ok_mode);

	lcd_instruct(LCD_SetPosition | LCD_LINE_TWO);
	lcd_sendString(buffer);
	lcd_sendString(celsius);
}