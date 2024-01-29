// Main program to build the application
// Has main(); does initialization and cleanup, and includes the game loop in this case.

#include <stdio.h>
#include <stdbool.h>
#include "hal/led.h"
#include "hal/joystick.h"
#include "time_helpers.h"
#include "utils.h"
#include<time.h>
#include<stdlib.h>

int main()
{
    // Initialize all modules; HAL modules first
    joystick_init();
    
    // Main program logic:-

    printf("%s","Hello embedded world, from Peter!\n\n");

    srand(time(NULL));

    for(int i = 0; i < NUM_LEDS; i++) {

        led_setTrigger(i,"none");

    }

    led_turnOffAll();

    printf("%s","Welcome to: Der-Finger-Poken und Der-Lighten-Blinken!\n\nWhen a single LED lights up, press the joystick in that direction!\n(Press left or right after prompted to push in a direction to exit)\n");

    long time_timeout = 5000;
    long long time_stopwatch;
    double time_forGetReady;
    long time_reaction;
    long time_best = time_timeout;

    bool pressedTooSoon;
    
    enum Direction correctDirection;

    while(1) {

        led_turnOffAll();
    /* 
        1. Print a "get ready" message and turn on the middle two LEDs on BBG.
    */
        printf("Get Ready..!\n");

        for(int i = 1; i < 3; i++) {

            led_setBrightness(i, "1");
        }
    /*
        2. If the user is pressing the joystick, tell them "Please let go of joystick"
        and wait until the joystick is not pressing.
    */
        if(joystick_isPressed()) {

            printf("%s","Please release the joystick to resume the game.\n");
            while(joystick_isPressed()) {}
        }

        pressedTooSoon = false;
        
        time_forGetReady = (double)1000 * utils_randomRange(0.5,3.0);

        time_stopwatch = time_getTimeInMs();

        // 3. Wait a random amount of time between 0.5 and 3.0s.
        while(time_forGetReady >= (time_getTimeInMs() - time_stopwatch)) {
        /* 
            4. If the user is pressing the joystick up or down, tell them "too soon"
                and go back to step 1.
        */
            if(joystick_getCurrentDirection() == UP || joystick_getCurrentDirection() == DOWN) {

                printf("Too Soon! Try again.\n");
                pressedTooSoon = true;
                time_sleepForMs(500);
                break;
            }
            // according to the instructions, left and right should not exit at this step
            // else if(joystick_getCurrentDirection() == LEFT || joystick_getCurrentDirection() == RIGHT) {
            //     utils_exitGameByUser();
            // }
            
        }

        // this reverts the game back to step 1
        if(pressedTooSoon) {

            continue;
        }

        // 5. pick a random direction (up or down)... 
        int direction = utils_randomFlipCoin(UP, DOWN);

        /*
         ...and print the direction name to the screen.
         display the program's chosen direction on the BBG's LEDs
        */
        led_turnOffAll();

        time_stopwatch = time_getTimeInMs();
        if(UP == direction) {

            printf("Push UP!!\n");
            correctDirection = UP;
            led_setBrightness(0,"1");
        }
        else if(DOWN == direction) {

            printf("Push DOWN!!\n");
            correctDirection = DOWN;
            led_setBrightness(3,"1");
        }
        else {

            printf("Not sure how this happened...\n");
            exit(1);
        }
        
        while(time_timeout > (time_getTimeInMs() - time_stopwatch) && !joystick_isPressed()){}

        led_turnOffAll();
        // If timer >5s, exit program with a message without waiting for a joystick press.
        if(time_timeout <= time_getTimeInMs() - time_stopwatch) {

            printf("Still there? No input for %ldms. Goodbye!\n",time_timeout);
            return 0;
        }
        /*
         7. Time how long it takes for the user to press the joystick in any (either?) direction.
         8. Process the user's joystick press
        */
        else if(correctDirection == joystick_getCurrentDirection()) {

            time_reaction = time_getTimeInMs() - time_stopwatch;
            printf("Correct!\n");

            if(time_reaction < time_best) {

                if(time_best != time_timeout) {

                    printf("%s%ld%s%ld%s","Your reaction time was ",time_reaction,"ms; that beats your current best of ",time_best,"ms!\n");
                    time_best = time_reaction;
                }
                else {

                    printf("%s%ld%s","Your reaction time was ",time_reaction,"ms.\n");
                    time_best = time_reaction;
                }
            }

            else {

                printf("%s%ld%s%ld%s","Your reaction time was ",time_reaction,"ms; current best is ",time_best,"ms.\n");
            }

            led_flashAll(4,0.5);
        }

        else if(LEFT == joystick_getCurrentDirection() || RIGHT == joystick_getCurrentDirection()) {

            led_turnOffAll();
            utils_exitGameByUserSuccess();
        }

        else {
            
            printf("Incorrect.\n");
            led_flashAll(10,1.0);
        }

        // uncomment to give some time to look at score
        // time_sleepForMs(2000);

    }
    
    return 0;

}
