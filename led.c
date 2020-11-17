#include <avrio.h>
#include "led.h"
#include "dht.h"


void led_init(void) {
	//Sets LED pins to output initializing further usage:
	LED_GREEN_DDR |= _BV(LED_GREEN_BIT);
	LED_RED_DDR |= _BV(LED_RED_BIT);
	LED_YELLOW_DDR |= _BV(LED_RED_BIT);
}

void led_state(uint8_t temp) {
	if (temp >= MAX_TEMP - WARNING_DEFICIT) YELLOW_TOGGLE;
	else if (temp >= MAX_TEMP) RED_TOGGLE;
	if (temp >= MIN_TEMP - WARNING_DEFICIT) YELLOW_TOGGLE;
	else if (temp <= MIN_TEMP) RED_TOGGLE;
	else { GREEN_TOGGLE };
}
