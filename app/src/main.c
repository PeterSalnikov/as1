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

void joystick_getCurrentDirection()
{
    // just a 5-way conditional that sees whose value is 0, if any?
    // run this in an event loop and react to the value it changes to?
    FILE *up = fopen("/sys/class/gpio/gpio26/value","r");
    if(up == NULL) {
        printf("ERROR: joystick_getCurrentDirection: \"UP\" binding not found\n");
        exit(1);
    }
    printf("%c\n",fgetc(up));
    fclose(up);
    // return NONE;
}

int main()
{
    // Initialize all modules; HAL modules first
    button_init();
    // printf("here");
    struct LED *leds = led_init();

// testing out some functions
    for(int i = 0; i < NUM_LEDS; i++) {

        // int brightnessChanged = fprintf(leds[i].brightness,"%d",i % 2);
        led_setTrigger(leds[i].trigger,"none");

        led_setBrightness(leds[i].brightness,"0");
    }

    // led_cleanup(leds);
    // Main program logic:-
    // // Print a "get ready" message and turn on the middle two LEDs on BBG.
    printf("Get Ready..!");
    for(int i = 1; i < 3; i++) {
        led_setBrightness(leds[i].brightness, "0");
    }

    // // if the user is pressing the joystick, tell them "Please let go of joystick" and wait until the joystick is not pressing.

    while(1) {
        leds = led_init();
        for(int i = 1; i < 3; i++) {
            led_setBrightness(leds[i].brightness, "0");
        }
        led_cleanup(leds);
        sleepForMs(100);
        
        joystick_getCurrentDirection();
        leds = led_init();
        for(int i = 1; i < 3; i++) {
            led_setBrightness(leds[i].brightness, "1");
        }
        led_cleanup(leds);
        sleepForMs(100);

    }


    button_cleanup();

    printf("!!! DONE !!!\n"); 

    return 0;

}