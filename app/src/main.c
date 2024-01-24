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
    struct LED *leds = led_init();

// testing out some functions
    for(int i = 0; i < NUM_LEDS; i++) {

        // int brightnessChanged = fprintf(leds[i].brightness,"%d",i % 2);
        led_setTrigger(leds[i].trigger,"none");

        led_setBrightness(leds[i].brightness,"0");
    }

    // led_cleanup(leds);
    // Main program logic:
    // Print a "get ready" message and turn on the middle two LEDs on BBG.
    printf("Get Ready..!");
    for(int i = 1; i < 3; i++) {
        led_setBrightness(leds[i].brightness, "1");
    }

    // if the user is pressing the joystick, tell them "Please let go of joystick" and wait until the joystick is not pressing.

    button_cleanup();

    printf("!!! DONE !!!\n"); 

}