#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h" 

#define LED_PIN_RED 11
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 13


bool repeating_timer_callback(struct repeating_timer *t) {
    if (!gpio_get(LED_PIN_RED) && !gpio_get(LED_PIN_YELLOW)) {
        gpio_put(LED_PIN_RED, !gpio_get(LED_PIN_RED));  
        if (gpio_get(LED_PIN_GREEN)) {
            gpio_put(LED_PIN_GREEN, !gpio_get(LED_PIN_GREEN));
        }             
    } else if (gpio_get(LED_PIN_RED) && !gpio_get(LED_PIN_YELLOW) && !gpio_get(LED_PIN_GREEN)) {
        gpio_put(LED_PIN_RED, !gpio_get(LED_PIN_RED));
        gpio_put(LED_PIN_YELLOW, !gpio_get(LED_PIN_YELLOW));
    } else if (!gpio_get(LED_PIN_RED) && gpio_get(LED_PIN_YELLOW) && !gpio_get(LED_PIN_GREEN)) {
        gpio_put(LED_PIN_YELLOW, !gpio_get(LED_PIN_YELLOW));
        gpio_put(LED_PIN_GREEN, !gpio_get(LED_PIN_GREEN));
    }
}

int main()
{
    stdio_init_all();

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED,true);

    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW,true);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN,true);

    gpio_put(LED_PIN_RED, !gpio_get(LED_PIN_RED));  

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        printf("Temporizacao com hardware\n");
        sleep_ms(1000);
    }
}
