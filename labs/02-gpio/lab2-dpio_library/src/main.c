/***********************************************************************
 * 
 * Blink a LED in Arduino-style and use function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2022 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/
// Arduino style 530 Bytes
// Registers 206 Bytes
// Library functions 188 Bytes

/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5   // PB5 is AVR pin where green on-board LED 
#define LED_BLUE PB0     // is connected
#define LED_GREEN_2 PB1
#define LED_D PB2
#define BTN PB3
#define SHORT_DELAY 500 // Delay in milliseconds
#ifndef F_CPU
#define F_CPU 16000000 // CPU frequency in Hz required for delay funcs
#endif

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>     // AVR device-specific IO definitions
#include <util/delay.h> // Functions for busy-wait delay loops
#include <gpio.h>

// -----
// This part is needed to use Arduino functions but also physical pin
// names. We are using Arduino-style just to simplify the first lab.
// #include "Arduino.h"
// #define PB5 13          // In Arduino world, PB5 is called "13"
// #define PB0 8
// #define PB1 9
// -----


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle one LED and use delay library.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    uint8_t led_value = 0;  // Local variable to keep LED status

    /*
    // Set pin where on-board LED is connected as output
    //Ver 1: Arduino style
    pinMode(LED_GREEN, OUTPUT);
    pinMode(LED_BLUE, OUTPUT);
    pinMode(LED_GREEN_2, OUTPUT);
    
    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        // Change LED value
        if (led_value == 0) {
            led_value = 1;
            // Set pin to HIGH
            // digitalWrite(LED_GREEN, HIGH);
            // digitalWrite(LED_BLUE, HIGH);
            // digitalWrite(LED_GREEN_2, LOW);
        }
        else {
            led_value = 0;
            // Clear pin to LOW
            // digitalWrite(LED_GREEN, LOW);
            // digitalWrite(LED_BLUE, LOW);
            // digitalWrite(LED_GREEN_2, HIGH);

        }
    }

    // Will never reach this
    return 0;
    */

    /*
    //Ver 2: Low-level (register) style
    DDRB = DDRB | (1<<LED_GREEN);
    DDRB = DDRB | (1<<LED_BLUE);
    DDRB = DDRB | (1<<LED_GREEN_2);


    // Infinite loop
    while (1)
    {
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        // Change LED value
        if (led_value == 0) {
            led_value = 1;
            // Set pin to HIGH
            PORTB = PORTB | (1<<LED_GREEN);
            PORTB = PORTB & ~(1<<LED_BLUE);
            PORTB = PORTB | (1<<LED_GREEN_2);
        }
        else {
            led_value = 0;
            // Clear pin to LOW
            PORTB = PORTB & ~(1<<LED_GREEN);
            PORTB = PORTB | (1<<LED_BLUE);
            PORTB = PORTB & ~(1<<LED_GREEN_2);

        }
    }
    
    // Will never reach this
    return 0;
    */

    //Ver 3: Libraries functions
    GPIO_mode_output(&DDRB, LED_GREEN);
    GPIO_mode_output(&DDRB, LED_BLUE);
    GPIO_mode_output(&DDRB, LED_D);
    GPIO_mode_input_pullup(&DDRB, BTN);

    // Infinite loop
    while (1)
    {
        while(GPIO_read(&PIND, BTN) == 1)
        // Pause several milliseconds
        _delay_ms(SHORT_DELAY);

        // Change LED value
        
        {
            if (led_value == 0) {
                led_value = 1;
                // Set pin to HIGH
                GPIO_write_high(&PORTB, LED_GREEN);
                GPIO_write_low(&PORTB, LED_BLUE);
                GPIO_write_high(&PORTB, LED_D);
            }
            else {
                led_value = 0;
                // Clear pin to LOW
                GPIO_write_low(&PORTB, LED_GREEN);
                GPIO_write_high(&PORTB, LED_BLUE);
                GPIO_write_low(&PORTB, LED_D);

            }
        }


    }

    // Will never reach this
    return 0;



}