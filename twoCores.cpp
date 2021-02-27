#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"

void printBoardID()
{
    pico_unique_board_id_t board_id;
    pico_get_unique_board_id(&board_id);

    for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; ++i)
        printf(" %02x", board_id.id[i]);

    printf("\n");
}

/* References for this implementation:
 * raspberry-pi-pico-c-sdk.pdf, page 68. 
 * pico-examples/adc/adc_console/adc_console.c
 * https://www.twilio.com/blog/programming-raspberry-pi-pico-microcontroller-micropython */
const float readOnboardTemperature(const char unit='C')
{
    // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
    const float conversionFactor = 3.3f / (1 << 12);

    adc_select_input(4);
    float adc = adc_read() * conversionFactor;

    float tempC = 27.0 - (adc - 0.706) / 0.001721;

    if(unit == 'C')
        return tempC;
    else if(unit == 'F')
        return tempC * 9 / 5 + 32;
    else return -1.0;
}

int main() 
{
    const uint LED_PIN = 25;

    stdio_init_all();
    adc_init();
    adc_set_temp_sensor_enabled(true);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    printf("Hello! ;)\n");
    printf("I am RPi Pico UID ");
    printBoardID();

    while (true)    
    {
        gpio_put(LED_PIN, 1);

        printf("Temp = %.02f\n", readOnboardTemperature('C'));

        sleep_ms(10);
    
        gpio_put(LED_PIN, 0);
        sleep_ms(990);
    }

    return 0;
}
