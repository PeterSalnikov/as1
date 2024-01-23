// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include "badmath.h"
#include "hal/button.h"
#include "hal/led.h"
#include<time.h>
#include<stdlib.h>



int main()
{

    // Initialize all modules; HAL modules first
    button_init();
    struct LED leds = led_init();
    int brightnessChanged = fprintf(leds.brightness,"1");
    if(brightnessChanged <= 0)
        printf("are you happy now\n");
    // led_cleanup(leds);
    // Main program logic:
    // Print a "get ready" message and turn on the middle two LEDs on BBG.
    printf("Get Ready..!");


    button_cleanup();

    printf("!!! DONE !!!\n"); 

}