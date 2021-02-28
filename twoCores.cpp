#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/unique_id.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/multicore.h"

/* Main task for second core. */
void core1_main()
{
    const uint LED_PIN = 25;

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    /* Note that the delay time below is not previously defined. This is just
     *   add randomness in repeat period just to visualize better the 
     *   independence between the tasks of core 0 (main) and core 1 (this). */

    while (true)    
    {
        gpio_put(LED_PIN, 1);
        sleep_ms(rand() >> 23);
        gpio_put(LED_PIN, 0);
        sleep_ms(rand() >> 22);
    }

    return;
}

/* Reference:
 *   pico-examples/system/unique_board_id
 */
void printBoardID()
{
    pico_unique_board_id_t board_id;
    pico_get_unique_board_id(&board_id);

    for (int i = 0; i < PICO_UNIQUE_BOARD_ID_SIZE_BYTES; ++i)
        printf("%02x", board_id.id[i]);
}

/* References:
 * raspberry-pi-pico-c-sdk.pdf, page 68. 
 * pico-examples/adc/adc_console/adc_console.c
 * https://www.twilio.com/blog/programming-raspberry-pi-pico-microcontroller-micropython */
const float readOnboardTemperature(const char unit)
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
    stdio_init_all();
    adc_init();
    adc_set_temp_sensor_enabled(true);

    /* This is just to make time for the user to open its serial monitor. 
     *   Otherwise the UID will not be seen. */
    sleep_ms(10000);

    printf("\n\nHello! I am RPi Pico UID ");
    printBoardID();
    printf("\n\n");

    /* Start the second core and its task. */
    multicore_launch_core1(core1_main);

    /* Continue with the main core's recurrent task. */
    while (true)
    {
        printf("Temp: %.02f C\n", readOnboardTemperature('C'));
        sleep_ms(1000);
    }

    return 0;
}
