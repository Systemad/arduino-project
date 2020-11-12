#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>
#include "helpers.h"


void main(void)
{   
    GREEN_OUTPUT();
    YELLOW_OUTPUT();
    RED_OUTPUT();

    while (1)
    {
        /*
        RED_TOGGLE();
        YELLOW_TOGGLE();
        GREEN_TOGGLE();
        _delay_ms(1000);
        */
    }
}
