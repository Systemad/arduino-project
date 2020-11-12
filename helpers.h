#define GREEN_LED 5
#define RED_LED 4
#define YELLOW_LED 3

#define GREEN_OUTPUT()   (DDRD |= _BV(GREEN_LED))
#define GREEN_TOGGLE()     (PORTD ^= _BV(GREEN_LED))

#define RED_OUTPUT()   (DDRD |= _BV(RED_LED))
#define RED_TOGGLE()     (PORTD ^= _BV(RED_LED))

#define YELLOW_OUTPUT()   (DDRD |= _BV(YELLOW_LED))
#define YELLOW_TOGGLE()     (PORTD ^= _BV(YELLOW_LED))
