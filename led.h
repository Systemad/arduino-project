#ifndef _LED_H_
#define _LED_H_

//Ports, bits and data registers for 3 LEDs:
#define LED_GREEN_PORT	PORTB
#define LED_GREEN_BIT	8
#define LED_GREEN_DDR	DDRB

#define LED_YELLOW_PORT PORTB
#define LED_YELLOW_BIT	1
#define LED_YELLOW_DDR	DDRB

#define LED_RED_PORT	PORTB
#define LED_RED_BIT		10
#define LED_RED_DDR		DDRB

#define GREEN_ON()       PORTB |= (1 << LED_GREEN_BIT)
#define GREEN_OFF()      PORTB &= ~(1 << LED_GREEN_BIT)

#define YELLOW_ON()      PORTB |= (1 << LED_YELLOW_BIT)
#define YELLOW_OFF()     PORTB &= ~(1 << LED_YELLOW_BIT)

#define RED_ON()         PORTB |= (1 << LED_RED_BIT)
#define RED_OFF()        PORTB &= ~(1 << LED_RED_BIT)


void led_init(void);

void led_state(int8_t temp);

#endif // !_LED_H_
