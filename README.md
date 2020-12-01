# This is an Arduino project done by Me and chairsitter@github

The project is a temperature warning system. It uses the components DHT11 temperature sensor, LCD 16x2 screen (can be found with Arduino starter kit), and 3 LEDs (Green, Yellow and Red). It functions by a library for DHT11 and LCD that was written by us with the help of datasheets.

NOTE: In order to test whether the project work correctly, use `lcdtesting` branch. It uses a simple counter inside main function, which is passes to led_state(), the function that controls what state the program is currently in.

## Components - What does what

DHT11 (3 Pin) - The DHT11 sensor's only assignment is to gather the temperature, which we will store as a variable as pass to led_state() which is the logic handler to determine what state we are in.

16x2 LCD - The LCD prints out the temperature on line 2, and what current mode the system is in on line 1.

Red, yellow, and green LED's job is to indicate what mode the system is in by blinking a LED.

## Modes - How it functions

The idea of how the program functions are simple and based on 3 different modes.

OK mode - If the temperature is between two defined values, the LCD will print out "OK" alongside the given temperature and light constant green LED.

Warning mode - If the temperature is on the rise or fall above/below the defined critical temperature, the LCD will print out "Warning" alongside the temperature and blink the yellow LED.

Critical mode - If the temperature is or has risen or fallen above/below defined critical temperature, the LCD will change its text to "Critical" alongside the temperature and blink the red LED.


## Code

DHT.C/H: Library we use to gather the temperature. 

LCD.C/H: Library we use to operate the LCD.

LED.C/H: Simple LED macros to turn off / on the LEDs. This file also includes the logic handler on which state the program is in. It also includes a function for each state.

SERIAL.C/H: UART functions that we used for debugging.

## Schematics

## DHT
<img src="https://raw.githubusercontent.com/Systemad/arduino-project/resources/Schematics/DHT/DHT_Schematic.png" alt="alt text" width="700" height="500">


## LCD
<img src="https://raw.githubusercontent.com/Systemad/arduino-project/resources/Schematics/LCD/LCD_Schematic.png" alt="alt text" width="700" height="500">


## LEDs
<img src="https://raw.githubusercontent.com/Systemad/arduino-project/resources/Schematics/LED/LED_Schematic.png" alt="alt text" width="700" height="500">
