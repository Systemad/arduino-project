#ifndef _LED_H_
#define _LED_H_

#define GREEN_ON()       (PORTB |= (1 << PB0));
#define GREEN_OFF()      (PORTB &= ~(1 << PB0));

#define YELLOW_ON()      (PORTB |= (1 << PB1));
#define YELLOW_OFF()     (PORTB &= ~(1 << PB1));

#define RED_ON()         (PORTB |= (1 << PB2));
#define RED_OFF()        (PORTB &= ~(1 << PB2));


void led_init(void);

void led_state(int8_t temp);

void warning(void);

void critical(void);

void ok(void);

#endif // !_LED_H_
