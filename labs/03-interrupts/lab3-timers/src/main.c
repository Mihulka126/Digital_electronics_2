/***********************************************************************
 * 
 * Blink two LEDs using functions from GPIO and Timer libraries. Do not 
 * use delay library any more.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2018 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#define LED_GREEN PB5  // Arduino Uno on-board LED
#define LED_RED PB2    // External active-low LED
#define LED_GREEN_2 PB3


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include <gpio.h>           // GPIO library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC


/* Function definitions ----------------------------------------------*/
/**********************************************************************
 * Function: Main function where the program execution begins
 * Purpose:  Toggle two LEDs using the internal 8- and 16-bit 
 *           Timer/Counter.
 * Returns:  none
 **********************************************************************/
int main(void)
{
    // Set pins where LEDs are connected as output
    GPIO_mode_output(&DDRB, LED_GREEN);
    GPIO_mode_output(&DDRB, LED_RED);
    GPIO_mode_output(&DDRB, LED_GREEN_2);

    // Configuration of 16-bit Timer/Counter1 for LED blinking
    // Set the overflow prescaler to 262 ms and enable interrupt
    TIM1_OVF_262MS
    TIM1_OVF_ENABLE

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines, ISRs */
    }

    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
 * Function: Timer/Counter1 overflow interrupt
 * Purpose:  Toggle on-board LED.
 **********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // PORTB = PORTB ^ (1<<LED_GREEN);
    // PORTB = PORTB ^ (1<<LED_GREEN_2);
    // PORTB = PORTB ^ (1<<LED_RED);

    static uint8_t no_of_overflows = 0;

    no_of_overflows++;
    if (no_of_overflows >= 6)
    {
        no_of_overflows = 0;
        PORTB = PORTB ^ (1<<LED_GREEN);
        PORTB = PORTB ^ (1<<LED_GREEN_2);
        
    }

    
    // Change 8-bit timer value anytime it overflows
    // TCNT0 = 128;
    // Overflow time: t_ovf = 1/f_cpu * (2^bit-init) * prescaler
    // Normal counting:
    // TCNT0 = 0, 1, 2, ...., 128, 129, ...., 254, 255, 0, 1
    //        |---------------------------------------|
    //                         16 ms
    // t_ovf = 1/16e6 * 256 * 1024 = 16 ms
    //
    // Shortened counting:
    // TCNT0 = 0, 128, 129, ...., 254, 255, 0, 128, ....
    //        |---------------------------|
    //                     8 ms
    // t_ovf = 1/16e6 * (256-128) * 1024 = 8 ms
}