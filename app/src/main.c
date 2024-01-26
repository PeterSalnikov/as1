// Main program to build the application
// Has main(); does initialization and cleanup and perhaps some basic logic.

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
    
    printf("%s","Hello embedded world, from Peter!\n\n");

    srand(time(NULL));

    for(int i = 0; i < NUM_LEDS; i++) {

        led_setTrigger(i,"none");

        led_setBrightness(i,"0");
    }

    // Main program logic:-
    // // Print a "get ready" message and turn on the middle two LEDs on BBG.
    // optional countdown for before the game starts

    printf("%s","Welcome to: Der-Finger-Poken und Der-Lighten-Blinken!\n\nWhen a single LED lights up, press the joystick in that direction!\n(Press left or right after prompted to push in a direction to exit)\n");

    // printf("Game begins in...\n");

    // for(int i = 5; i > 0; i--) {
    //     printf("%d!\n",i);
    //     time_sleepForMs(1000);
    // }
    // // if the user is pressing the joystick, tell them "Please let go of joystick" and wait until the joystick is not pressing.

    long timeOutTime = 5000;

    bool gameOn = false;
    long long time_sinceGameStart = 0;
    long reactionTime = 0;
    long bestTime = timeOutTime;
    enum Direction correctDirection = UP;

    while(1) {

        gameOn = false;

        led_turnOffAll();


        if(joystick_isPressed() && gameOn == false) {
            printf("%s","Please release the joystick to resume the game.\n");
            while(joystick_isPressed()) {

            }
        }

        for(int i = 1; i < 3; i++) {
            led_setBrightness(i, "1");
        }

        printf("Get Ready..!\n");

        time_sleepForMs((double)1000 * random_wait(0.5,3.0));

        led_turnOffAll();

        enum Direction direction = random_upDown();

        gameOn = true;
        time_sinceGameStart = time_getTimeInMs();
        if(UP == direction) {
            printf("Push UP!!\n");
            correctDirection = UP;
            led_setBrightness(0,"1");
        }
        else if(DOWN == direction) {
            correctDirection = DOWN;
            printf("Push DOWN!!\n");

            led_setBrightness(3,"1");
        }
        else {
            printf("I'm not sure how this happened...\n");
            exit(1);
        }
        
        while(timeOutTime > (time_getTimeInMs() - time_sinceGameStart) && !joystick_isPressed()){}

        led_turnOffAll();

        if(timeOutTime <= time_getTimeInMs() - time_sinceGameStart) {
            printf("Still there? No input for 5000ms. Goodbye!\n");
            return 0;
        }

        else if(correctDirection == joystick_getCurrentDirection()) {
            reactionTime = time_getTimeInMs() - time_sinceGameStart;

            printf("Correct!\n");

            // timeOutTime checked here so it doesn't display the initial min as a previous score.
            if(reactionTime < bestTime && bestTime != timeOutTime) {

                printf("%s%ld%s%ld%s","Your reaction time was ",reactionTime,"ms; that beats your current best of ",bestTime,"ms!\n");
                bestTime = reactionTime;
            }
            else if(reactionTime >= bestTime && bestTime != timeOutTime) {

                printf("%s%ld%s%ld%s","Your reaction time was ",reactionTime,"ms; current best is ",bestTime,"ms.\n");
            }
            else {
                printf("%s%ld%s","Your reaction time was ",reactionTime,"ms.\n");
                bestTime = reactionTime;
            }
            led_flashAll(4,0.5);
        }

        else if(LEFT == joystick_getCurrentDirection() || RIGHT == joystick_getCurrentDirection()) {
            if(bestTime == timeOutTime) {
                printf("%s","You have ended the game.\nYou did not set a time for this session. Goodbye!\n");
            }
            else {
                printf("%s%ld%s","You have ended the game.\nYour personal best for this session was ",bestTime,"ms. Goodbye!\n");
            }

            led_turnOffAll();

            break;

        }

        else {
            printf("Incorrect.\n");
            led_flashAll(10,1.0);
        }

        // just for pacing, to give some time to look at your score
        time_sleepForMs(2000);

    }

    printf("!!! EXITING PROGRAM !!!\n"); 

    return 0;

}