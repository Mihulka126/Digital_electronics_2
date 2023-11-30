#include <avr/io.h>
#include <avr/interrupt.h>
#include <time.h>
#include <moist_sens.h>


/*****************************************************
 * Function: cmd_comm()
 * Purpose: Communication between user and program
 * Input: None
 * Returns: None
******************************************************/

void cmd_comm(void){
    
    // By typing different letters into command line this finction shows help menu or data form sensors
    uint8_t value;          // Selected letter is saved into this variable
    uint16_t moisture = 50;      // Soil Moisture is saved here
    uint8_t humidity = 60;       // Air humidity is saved here
    uint8_t temperature = 25;    // Air temperature is saved here
    char string[8];  // String for converted numbers by itoa()

    value = uart_getc();
    if (value =! 0) {  // Data available from UART
        
        switch (value)
        {
        case 63:    // By typing '?' into command line the Help menu is shown
            uart_puts("\nHelp: \n");
            uart_puts("? - Show help\n");
            uart_puts("a - Show every information");
            uart_puts("m - Show soil moisture\n");
            uart_puts("t - Show air temperature\n");
            uart_puts("h - Show air humidity\n");
            uart_puts("c - Show current time and date\n");
            break;

        case 109:   // By typing 'm' program will give you current soil moisture
            uart_puts("Soil moisture: ");
            moisture = get_moist();
            itoa(moisture, string, 10);
            uart_puts(string);
            uart_puts(" %%\n");
            break;

        case 116:   // By typing 't' program will give you current air temperature
            uart_puts("Air temperature: ");
            // temperature = get_temperature();
            itoa(temperature, string, 10);
            uart_puts(string);
            uart_puts(" °C\n");
            break;

        case 104:   // By typing 'h' program will give you current air humidity
            uart_puts("Air humidity: ");
            // humidity = get_humidity();
            itoa(humidity, string, 10);
            uart_puts(string);
            uart_puts(" %%\n");
            break;

        case 99:    // By typing 'c' program will give you current time
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            uart_puts("Current time and date: ");
            uart_puts(asctime(timeinfo));
            uart_puts("\n");
            break;

        case 97:    // By typing 'a' program will give every current information
            // Time
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            uart_puts("Current time and date: ");
            uart_puts(asctime(timeinfo));
            uart_puts("\n");
            
            // Temperature
            uart_puts("Air temperature: ");
            // temperature = get_temperature();
            itoa(temperature, string, 10);
            uart_puts(string);
            uart_puts(" °C\n");

            // Humidity
            uart_puts("Air humidity: ");
            // humidity = get_humidity();
            itoa(humidity, string, 10);
            uart_puts(string);
            uart_puts(" %%\n");
            
            // Moisture
            uart_puts("Soil moisture: ");
            moisture = get_moist();
            itoa(moisture, string, 10);
            uart_puts(string);
            uart_puts(" %%\n");

        default:    // When you type different letter the program will try to help you
            uart_puts("Wrong letter was typed. Type \x27h\x27 for help");
            break;
        }

        uart_putc('\n');

    }


}