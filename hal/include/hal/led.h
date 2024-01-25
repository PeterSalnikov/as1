#ifndef _LED_H_
#define _LED_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUM_LEDS 4
#define BBG_LED_DIR "/sys/class/leds/beaglebone:green:usr"
#define LED_BUF 50

void led_setTrigger(int led_num, char *state);
void led_setBrightness(int led_num, char *level);

#endif