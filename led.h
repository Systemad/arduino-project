#ifndef _LED_H_
#define _LED_H_

//Ports, bits and data registers for 3 LEDs:
#define LED_GREEN_PORT	PORTB
#define LED_GREEN_BIT	8
#define LED_GREEN_DDR	DDRB

#define LED_YELLOW_PORT PORTB
#define LED_YELLOW_BIT	9
#define LED_YELLOW_DDR	DDRB

#define LED_RED_PORT	PORTB
#define LED_RED_BIT		10
#define LED_RED_DDR		DDRB

#define GREEN_TOGGLE()      (PORTB ^= _BV(LED_GREEN_BIT))
#define RED_TOGGLE()        (PORTB ^= _BV(LED_RED_BIT))
#define YELLOW_TOGGLE()     (PORTB ^= _BV(LED_YELLOW_BIT))


void led_init(void);

void led_state(uint8_t temp);

#endif // !_LED_H_
