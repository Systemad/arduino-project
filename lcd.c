#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"

void lcd_init() {

    LCD_D7_DDR |= (1 << LCD_D7_BIT);
    LCD_D6_DDR |= (1 << LCD_D6_BIT);
    LCD_D5_DDR |= (1 << LCD_D5_BIT);
    LCD_D4_DDR |= (1 << LCD_D4_BIT);

    LCD_E_DDR |= (1 << LCD_E_BIT);
    LCD_RS_DDR |= (1 << LCD_RS_BIT);

	_delay_ms(100);

	LCD_RS_PORT &= ~(1 << LCD_RS_BIT);             
	LCD_E_PORT &= ~(1 << LCD_E_BIT);                 

    lcd_sendByte(LCD_FunctionReset);
    _delay_ms(10);                                
    lcd_sendByte(LCD_FunctionReset);
    _delay_us(200);                                 
    lcd_sendByte(LCD_FunctionReset);
    _delay_us(200);                              


    lcd_sendByte(LCD_FunctionSet4bit);
    _delay_us(80);
    lcd_instruct(LCD_FunctionSet4bit);
    _delay_us(80);


    lcd_instruct(LCD_DisplayOff);     
    _delay_us(80);                              
    lcd_instruct(LCD_Clear);        
    _delay_ms(4);                                  
    lcd_instruct(LCD_EntryMode);       
    _delay_us(80);                           


    lcd_instruct(LCD_DisplayOn);        
    _delay_us(80);                           
}

void lcd_sendByte(uint8_t byte) {
    LCD_D7_PORT &= ~(1 << LCD_D7_BIT);                       
    if (byte & 1 << 7) LCD_D7_PORT |= (1 << LCD_D7_BIT);    
    LCD_D6_PORT &= ~(1 << LCD_D6_BIT);                       
    if (byte & 1 << 6) LCD_D6_PORT |= (1 << LCD_D6_BIT);
    LCD_D5_PORT &= ~(1 << LCD_D5_BIT);
    if (byte & 1 << 5) LCD_D5_PORT |= (1 << LCD_D5_BIT);
    LCD_D4_PORT &= ~(1 << LCD_D4_BIT);
    if (byte & 1 << 4) LCD_D4_PORT |= (1 << LCD_D4_BIT);

                                                       
    LCD_E_PORT |= (1 << LCD_E_BIT);               
    _delay_us(1);                                 
    LCD_E_PORT &= ~(1 << LCD_E_BIT);             
    _delay_us(1);                              
}


void lcd_instruct(uint8_t instruction) {
    LCD_RS_PORT &= ~(1 << LCD_RS_BIT);            
    LCD_E_PORT &= ~(1 << LCD_E_BIT);              
    lcd_sendByte(instruction);
    lcd_sendByte(instruction << 4);
}

void lcd_sendChar(uint8_t character) {
    LCD_RS_PORT |= (1 << LCD_RS_BIT);
    LCD_E_PORT &= ~(1 << LCD_E_BIT);
    lcd_sendByte(character);
    lcd_sendByte(character << 4);
}

//  WIP
//void lcd_sendInteger(int integer) {
//    LCD_RS_PORT |= (1 << LCD_RS_BIT);
//    LCD_E_PORT &= ~(1 << LCD_E_BIT);
//    lcd_sendByte(integer);
//    lcd_sendByte(integer << 4);
//}

void lcd_sendString(uint8_t string[]) {
    volatile int i = 0;
    while (string[i] != 0) {
        lcd_sendChar(string[i]);
        i++;
        _delay_us(80);
    }
}
