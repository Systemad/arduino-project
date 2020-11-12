#ifndef DHT_H_
#define DHT_H_

// Define pin mode and DHT11 pin
#define DHT_PIN PIND
#define DHT_INPUTPIN PD6
#define DHT_TIMEOUT 200

// Macros for DHT11 pin
#define DHT_PIN_INPUT()    (DDRD &= ~_BV(DHT_INPUTPIN))
#define DHT_PIN_OUTPUT()   (DDRD |= _BV(DHT_INPUTPIN))
#define DHT_PIN_LOW()      (PORTD &= ~_BV(DHT_INPUTPIN))
#define DHT_PIN_HIGH()     (PORTD |= _BV(DHT_INPUTPIN))
#define DHT_PIN_READ()     (PIND & _BV(DHT_INPUTPIN))


// Function to get temperature
int8_t dht_getdata(int8_t temperature);

#endif
