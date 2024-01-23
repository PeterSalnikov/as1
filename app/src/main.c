// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

#include <stdio.h>
#include <stdbool.h>
#include "badmath.h"
#include "hal/button.h"

#include<time.h>
#include<stdlib.h>
#define DA_TRIGGER_FILE_NAME_HERE "/sys/class/leds/beaglebone:green:usr0/trigger"
#define DA_BRIGHTNESS_FILE_NAME_HERE "/sys/class/leds/beaglebone:green:usr0/brightness"
int main()
{
    // printf("Hello world!\n");
    printf("Hello embedded world, from Peter!\n");

    // Initialize all modules; HAL modules first
    button_init();
    badmath_init();
    // Main program logic:
    // for (int i = 0; i < 10; i++) {
    //     printf("  -> Reading button time %d = %d\n", i, button_is_button_pressed());
    // }

    // for (int i = 0; i <= 35; i++) {
    //     int ans = badmath_factorial(i);
    //     printf("%4d! = %6d\n", i, ans);
    // }

    FILE *pLedTriggerFile = fopen(DA_TRIGGER_FILE_NAME_HERE, "w");
    FILE *pLedBrightnessFile = fopen(DA_BRIGHTNESS_FILE_NAME_HERE, "w");

    if(pLedTriggerFile == NULL) {
        printf("ERROR OPENING %s.", DA_TRIGGER_FILE_NAME_HERE);
        exit(1);
    }
    if(pLedBrightnessFile == NULL) {
        printf("ERROR OPENING %s.", DA_TRIGGER_FILE_NAME_HERE);
        exit(1);
    }
    int charWritten = fprintf(pLedTriggerFile, "none");
    if(charWritten <= 0) {
        printf("ERROR WRITING DATA");
        exit(1);
    }

    int brightnessChanged = fprintf(pLedBrightnessFile, "0");
    if(brightnessChanged <= 0) {
        printf("ERROR WRITING DATA");
        exit(1);
    }
    printf("LED modified successfully\n");
    fclose(pLedTriggerFile);
    fclose(pLedBrightnessFile);

    printf("Timing Test\n");

    for(int i = 0; i < 5; i++) {
        long seconds = 1;
        long nanoseconds = 500000000;
        struct timespec reqDelay = {seconds, nanoseconds};
        nanosleep(&reqDelay, (struct timespec *) NULL);
        printf("Delayed print %d.\n", i);
    }

    // Cleanup all modules (HAL modules last)
    badmath_cleanup();
    button_cleanup();

    printf("!!! DONE !!!\n"); 

    // Some bad code to try out and see what shows up.
    #if 0
        // Test your linting setup
        //   - You should see a warning underline in VS Code
        //   - You should see compile-time errors when building (-Wall -Werror)
        // (Linting using clang-tidy; see )
        int x = 0;
        if (x = 10) {
        }
    #endif
    #if 0
        // Demonstrate -fsanitize=address (enabled in the root CMakeFiles.txt)
        // Compile and run this code. Should see warning at compile time; error at runtime.
        int data[3];
        data[3] = 10;
        printf("Value: %d\n", data[3]);
    #endif
}