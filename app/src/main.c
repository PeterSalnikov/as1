// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include "badmath.h"
#include "hal/button.h"
#include "hal/led.h"
#include "hal/joystick.h"
#include<time.h>
#include<stdlib.h>

static void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 100000000;

    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}



int main()
{
    // Initialize all modules; HAL modules first
    button_init();

// testing out some functions
    for(int i = 0; i < NUM_LEDS; i++) {

        // int brightnessChanged = fprintf(leds[i].brightness,"%d",i % 2);
        led_setTrigger(i,"none");

        led_setBrightness(i,"0");
    }

    // Main program logic:-
    // // Print a "get ready" message and turn on the middle two LEDs on BBG.
    printf("Get Ready..!");
    for(int i = 1; i < 3; i++) {
        led_setBrightness(i, "0");
    }

    // // if the user is pressing the joystick, tell them "Please let go of joystick" and wait until the joystick is not pressing.

    while(1) {

        for(int i = 1; i < 3; i++) {
            led_setBrightness(i, "0");
        }

        sleepForMs(100);
        
        joystick_getCurrentDirection();

        for(int i = 1; i < 3; i++) {
            led_setBrightness(i, "1");
        }

        sleepForMs(100);

    }


    button_cleanup();

    printf("!!! DONE !!!\n"); 

    return 0;

}