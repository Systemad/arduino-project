#ifndef _LCD_H_
#define _LCD_H_

//Ports, bits and data registers for described pins in the LCD:
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
#define LCD_E_BIT	PORTB1
#define LCD_E_DDR	DDRB

#define LCD_RS_PORT	PORTB
#define LCD_RS_BIT	PORTB0
#define LCD_RS_DDR	DDRB


//Positions of the two lines:
#define LCD_LINE_ONE	0x00
#define LCD_LINE_TWO	0x40

//Instructions:
#define LCD_Clear           0b00000001     //Clear all characters    
#define LCD_Home            0b00000010     //Set the position back to the start of the first line   
#define LCD_EntryMode       0b00000110     //Swap direction of the cursor  
#define LCD_DisplayOff      0b00001000          
#define LCD_DisplayOn       0b00001100        
#define LCD_Reset			0b00110000       
#define LCD_Set4bit			0b00101000     
#define LCD_SetPosition     0b10000000    


void lcd_init(void);

void lcd_instruct(uint8_t instruction);

void lcd_sendByte(uint8_t byte);

void lcd_sendChar(uint8_t character);

void lcd_sendString(uint8_t *);

#endif // _LCD_H_
