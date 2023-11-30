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
    
    uint8_t value;
    uint16_t moisture;
    uint8_t humidity;
    uint8_t temperature;
    // uint8_t time;
    char string[8];  // String for converted numbers by itoa()

    value = uart_getc();
    if (value =! 0) {  // Data available from UART
        // Display ASCII code of received character
        
        switch (value)
        {
        case 63:
            uart_puts("\nHelp: \n");
            uart_puts("? - Show help\n");
            uart_puts("m - Show soil moisture\n");
            uart_puts("t - Show air temperature\n");
            uart_puts("h - Show air humidity\n");
            uart_puts("c - Show current time and date\n");
            break;

        case 109:
            uart_puts("Soil moisture: ");
            moisture = get_moist();
            itoa(moisture, string, 10);
            uart_puts(string);
            uart_puts(" %%\n");
            break;

        case 116:
            uart_puts("Air temperature: ");
            // temperature = get_temperature();
            itoa(temperature, string, 10);
            uart_puts(string);
            uart_puts(" °C\n");
            break;

        case 104:
            uart_puts("Air humidity: ");
            // humidity = get_humidity();
            itoa(humidity, string, 10);
            uart_puts(string);
            uart_puts(" %%\n");
            break;

        case 99:
            
            time_t rawtime;
            struct tm * timeinfo;
            time ( &rawtime );
            timeinfo = localtime ( &rawtime );
            uart_puts("Current time and date: ");
            uart_puts(asctime(timeinfo));
            uart_puts("\n");
            break;

        default:
            break;
        }

        uart_putc('\n');

    }


}