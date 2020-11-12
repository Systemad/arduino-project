#ifndef DHT_H_
#define DHT_H_

#define DHT_PIN PIND
#define DHT_INPUTPIN PD6

#define DHT_PIN_INPUT()    (DDRD &= ~_BV(DHT_INPUTPIN))
#define DHT_PIN_OUTPUT()   (DDRD |= _BV(DHT_INPUTPIN))
#define DHT_PIN_LOW()      (PORTD &= ~_BV(DHT_INPUTPIN))
#define DHT_PIN_HIGH()     (PORTD |= _BV(DHT_INPUTPIN))
#define DHT_PIN_READ()     (PIND & _BV(DHT_INPUTPIN))


#define DHT_TIMEOUT 200

int8_t dht_gettemperature(int8_t temperature);
int8_t dht_gethumidity(int8_t humidity);
int8_t dht_gettemperaturehumidity(int8_t temperature, int8_t humidity);

#endif
