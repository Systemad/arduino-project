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


    lcd_sendByte(LCD_FunctionSet4bit);          // Enables 4bit mode
    _delay_us(80);
    lcd_instruct(LCD_FunctionSet4bit);          // Set the size and font
    _delay_us(80);

    //Initialization routine:
    lcd_instruct(LCD_DisplayOff);               // Turns display OFF   
    _delay_us(80);                             
    lcd_instruct(LCD_Clear);                    // Clears RAM     
    _delay_ms(4);                                  
    lcd_instruct(LCD_EntryMode);                // Sets swap behaviour
    _delay_us(80);                           


    lcd_instruct(LCD_DisplayOn);                // Turns LCD on    
    _delay_us(80);                           
}

// Sends a byte to the LCD module:
void lcd_sendByte(uint8_t byte) {
    // Sets the data to 0 and then to 1 for every data bit:
    LCD_D7_PORT &= ~(1 << LCD_D7_BIT);                       
    if (byte & 1 << 7) LCD_D7_PORT |= (1 << LCD_D7_BIT);    
    LCD_D6_PORT &= ~(1 << LCD_D6_BIT);                       
    if (byte & 1 << 6) LCD_D6_PORT |= (1 << LCD_D6_BIT);
    LCD_D5_PORT &= ~(1 << LCD_D5_BIT);
    if (byte & 1 << 5) LCD_D5_PORT |= (1 << LCD_D5_BIT);
    LCD_D4_PORT &= ~(1 << LCD_D4_BIT);
    if (byte & 1 << 4) LCD_D4_PORT |= (1 << LCD_D4_BIT);

                                                       
    LCD_E_PORT |= (1 << LCD_E_BIT);             // E to high           
    _delay_us(1);                                 
    LCD_E_PORT &= ~(1 << LCD_E_BIT);            // E to low         
    _delay_us(1);                              
}


void lcd_instruct(uint8_t instruction) {
    LCD_RS_PORT &= ~(1 << LCD_RS_BIT);          // RS to low         
    LCD_E_PORT &= ~(1 << LCD_E_BIT);            // E to low     
    lcd_sendByte(instruction);                  // Uses the sendByte function to send 4 upper bits of data
    lcd_sendByte(instruction << 4);             // Send 4 lower bits
}

// Sends a byte containing a char to data register and outputs it on the LCD:
void lcd_sendChar(uint8_t character) {
    LCD_RS_PORT |= (1 << LCD_RS_BIT);           // RS to high
    LCD_E_PORT &= ~(1 << LCD_E_BIT);            // E to low
    lcd_sendByte(character);
    lcd_sendByte(character << 4);
}

// Iterates through the arrayed char and outputs every one to the LCD:
void lcd_sendString(uint8_t string[]) {
    volatile int i = 0;
    while (string[i] != 0) {
        lcd_sendChar(string[i]);
        i++;
        _delay_us(80);
    }
}
