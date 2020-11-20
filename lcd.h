#ifndef _LCD_H_
#define _LCD_H_

//Ports:
#define LCD_D7_PORT PORTD
#define LCD_D7_BIT	PORTD2
#define LCD_D7_DDR	DDRD

#define LCD_D6_PORT PORTD
#define LCD_D6_BIT	PORTD3
#define LCD_D6_DDR	DDRD

#define LCD_D5_PORT	PORTD
#define LCD_D5_BIT	PORTD4
#define LCD_D5_DDR	DDRD

#define LCD_D4_PORT	PORTD
#define LCD_D4_BIT	PORTD5
#define LCD_D4_DDR	DDRD

#define LCD_E_PORT	PORTB
#define LCD_E_BIT	PORTB3
#define LCD_E_DDR	DDRB

#define LCD_RS_PORT	PORTB
#define LCD_RS_BIT	PORTB4
#define LCD_RS_DDR	DDRB


//Positions:
#define LCD_LINE_ONE	0x00
#define LCD_LINE_TWO	0x40

//Instructions:
#define LCD_Clear           0b00000001         
#define LCD_Home            0b00000010         
#define LCD_EntryMode       0b00000110        
#define LCD_DisplayOff      0b00001000          
#define LCD_DisplayOn       0b00001100        
#define LCD_FunctionReset   0b00110000       
#define LCD_FunctionSet4bit 0b00101000     
#define LCD_SetCursor       0b10000000    


void lcd_init(void);

void lcd_instruct(uint8_t instruction);

void lcd_sendByte(uint8_t byte);

void lcd_sendChar(uint8_t character);

void lcd_sendString(uint8_t *);








#endif // _LCD_H_
