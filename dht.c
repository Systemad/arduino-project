/*
DHT Library 0x03

copyright (c) Davide Gironi, 2012

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "dht.h"


#define DHT_PIN_INPUT()    (DDRD &= ~_BV(DHT_INPUTPIN))
#define DHT_PIN_OUTPUT()   (DDRD |= _BV(DHT_INPUTPIN))
#define DHT_PIN_LOW()      (PORTD &= ~_BV(DHT_INPUTPIN))
#define DHT_PIN_HIGH()     (PORTD |= _BV(DHT_INPUTPIN))
#define DHT_PIN_READ()     (PIND & _BV(DHT_INPUTPIN))


#define DHT_DDR DDRD
#define DHT_PORT PORTD
#define DHT_PIN PIND
#define DHT_INPUTPIN PD6


int8_t dht_getdata(int8_t *temperature, int8_t *humidity) {
	uint8_t bits[5];
	uint8_t i,j = 0;

	memset(bits, 0, sizeof(bits));

	//reset port
	//DHT_DDR |= (1<<DHT_INPUTPIN); //output
	DHT_PIN_OUTPUT();

	//DHT_PORT |= (1<<DHT_INPUTPIN); //high
	DHT_PIN_HIGH();
	
	_delay_ms(100);

	//send request
	DHT_PIN_LOW();
	//DHT_PORT &= ~(1<<DHT_INPUTPIN); //low
	_delay_ms(18);
	DHT_PIN_HIGH();
	//DHT_PORT |= (1<<DHT_INPUTPIN); //high
	//DHT_DDR &= ~(1<<DHT_INPUTPIN); //input
	DHT_PIN_INPUT();
	_delay_us(40);

	//check start condition 1
	if((DHT_PIN & (1<<DHT_INPUTPIN))) {
		return -1;
	}
	_delay_us(80);
	//check start condition 2
	if(!(DHT_PIN & (1<<DHT_INPUTPIN))) {
		return -1;
	}
	_delay_us(80);

	//read the data
	uint16_t timeoutcounter = 0;
	for (j=0; j<5; j++) { //read 5 byte
		uint8_t result=0;
		for(i=0; i<8; i++) {//read every bit
			timeoutcounter = 0;
			while(!(DHT_PIN & (1<<DHT_INPUTPIN))) { //wait for an high input (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return -1; //timeout
				}
			}
			_delay_us(30);
			if(DHT_PIN & (1<<DHT_INPUTPIN)) //if input is high after 30 us, get result
				result |= (1<<(7-i));
			timeoutcounter = 0;
			while(DHT_PIN & (1<<DHT_INPUTPIN)) { //wait until input get low (non blocking)
				timeoutcounter++;
				if(timeoutcounter > DHT_TIMEOUT) {
					return -1; //timeout
				}
			}
		}
		bits[j] = result;
	}

	//reset port
	//DHT_DDR |= (1<<DHT_INPUTPIN); //output
	DHT_PIN_OUTPUT();
	//DHT_PORT |= (1<<DHT_INPUTPIN); //low
	DHT_PIN_LOW();
	_delay_ms(100);

	//check checksum
	if ((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]) {
		*temperature = bits[2];
		*humidity = bits[0];
		return 0;
	}

	return -1;
}

int8_t dht_gettemperature(int8_t *temperature) {
	int8_t humidity = 0;
	return dht_getdata(temperature, &humidity);
}

int8_t dht_gethumidity(int8_t *humidity) {
	int8_t temperature = 0;
	return dht_getdata(&temperature, humidity);
}

int8_t dht_gettemperaturehumidity(int8_t *temperature, int8_t *humidity) {
	return dht_getdata(temperature, humidity);
}
