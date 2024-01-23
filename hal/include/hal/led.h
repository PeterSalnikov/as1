#ifndef _LED_H_
#define _LED_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
// #define LED0_TRIGGER "/sys/class/leds/beaglebone:green:usr0/trigger"
// #define LED0_BRIGHTNESS "/sys/class/leds/beaglebone:green:usr0/brightness"

// #define LED1_TRIGGER "/sys/class/leds/beaglebone:green:usr1/trigger"
// #define LED1_BRIGHTNESS "/sys/class/leds/beaglebone:green:usr1/brightness"

// #define LED2_TRIGGER "/sys/class/leds/beaglebone:green:usr2/trigger"
// #define LED2_BRIGHTNESS "/sys/class/leds/beaglebone:green:usr2/brightness"

// #define LED3_TRIGGER "/sys/class/leds/beaglebone:green:usr3/trigger"
// #define LED3_BRIGHTNESS "/sys/class/leds/beaglebone:green:usr3/brightness"

#define NUM_LEDS 4
#define BBG_LED_DIR "/sys/class/leds/beaglebone:green:usr"

struct LED {

    FILE *trigger;
    FILE *brightness;

};

struct LED led_init();
// void led_cleanup();

#endif