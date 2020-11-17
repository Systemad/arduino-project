#include <stdio.h>
#include <string.h>
#include <avr/io.h>
#include <util/delay.h>

#include "dht.h"


void start_dht(){
	DHT_PIN_OUTPUT();
	DHT_PIN_HIGH();
	
	_delay_ms(100);

	// In order to send a request we need to set it to LOW, then wait 18ms (as specified in datasheet) 
	DHT_PIN_LOW();
	_delay_ms(18);
	
	// Then We need to set it HIGH and as INPUT in order to read the signals and data
	DHT_PIN_HIGH();
	DHT_PIN_INPUT();
	_delay_us(40);

	// Wait for the first respone to finish then delay for 80us
	while((DHT_PIN & _BV(DHT_INPUTPIN)));
	_delay_us(80);
	
	// Wait for the last respone to finish then delay for 80us
	while(!(DHT_PIN & _BV(DHT_INPUTPIN)));
	_delay_us(80);
}

void reset_dht(){

	// Now we need to reset the port by setting it to LOW and OUTPUT in order to read from it again
	DHT_PIN_OUTPUT();
	DHT_PIN_LOW();
	_delay_ms(100);

}

int8_t dht_getdata(int8_t temperature) {
	
	uint8_t bits[5];
	uint16_t counter = 0;

	memset(bits, 0, sizeof(bits));

	// Setup and start dht;
	start_dht();

	for (uint8_t j=0; j<5; j++) { 								// The actual data is stored in 5 bytes, but we need to read 6th as well for parity
		uint8_t result=0;
		for(uint8_t i=0; i<8; i++) {							// Now we read every bit of each 5 bytes
			counter = 0;
			while(!(DHT_PIN & _BV(DHT_INPUTPIN))) { 			// We initiate a counter to track how long it takes for an INPUT
				counter++;
				if(counter > DHT_TIMEOUT) {						// If this timer exceeds oue defined DHT_TIMEOUT, return -1
					return -1; 
				}
			}
			_delay_us(50);
			while(DHT_PIN & _BV(DHT_INPUTPIN)) 				// Now get the results and store them in results
				result |= _BV(7-i);

			counter = 0;
			while(DHT_PIN & _BV(DHT_INPUTPIN)) { 				// Same as before, but now we wait for it to get LOW
				counter++;						
				if(counter > DHT_TIMEOUT) {						// If this timer exceeds our defined DHT_TIMEOUT, return -1
					return -1;
				}
			}
		}
		bits[j] = result; // The data including parity
	}

	// Reset DHT in order to read data from it again
	reset_dht();
	
	/*
	* According to the datasheet, if the data is correct, the first 4 bytes together should be equal to the parity bit
	* we can check this by calculating first 4 bytes together and check if it equal to the parity bit
	* if it, store 3rd byte (High temperature 8) into temperature 
	*/ 

	if ((bits[0] + bits[1] + bits[2] + bits[3]) != bits[4]) {
		return -1;
	} else {
		temperature = bits[2];
	}

	return temperature;
}