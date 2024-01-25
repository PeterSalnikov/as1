#include "hal/joystick.h"

static bool is_initialized = false;

void joystick_init()
{
    // here, would check if all necessary GPIO pins are exported. In this assignment, not to worry
    is_initialized = true;
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