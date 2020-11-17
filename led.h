#ifndef _LED_H_
#define _LED_H_

//Ports, bits and data registers for 3 LEDs:
#define LED_GREEN_PORT	PORTD
#define LED_GREEN_BIT	PORTD5
#define LED_GREEN_DDR	DDRD

#define LED_RED_PORT	PORTD
#define LED_RED_BIT		PORTD4
#define LED_RED_DDR		DDRD

#define LED_YELLOW_PORT PORTD
#define LED_YELLOW_BIT	PORTD3
#define LED_YELLOW_DDR	DDRD


#define GREEN_TOGGLE     (PORTD ^= _BV(LED_GREEN_BIT))
#define RED_TOGGLE    (PORTD ^= _BV(LED_RED_BIT))
#define YELLOW_TOGGLE     (PORTD ^= _BV(LED_YELLOW_BIT))


void led_init(void);

void led_state(uint8_t temp);

#endif // !_LED_H_
