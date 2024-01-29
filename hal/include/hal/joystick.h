#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include<sys/mman.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

#ifndef JOYSTICK_H
#define JOYSTICK_H

#define NUM_JOYSTICK_DIRECTIONS 4
#define JOYSTICK_BUF 50
#define JOYSTICK_PATH "/sys/class/gpio/gpio"

enum Direction {
    UP = 26,
    DOWN = 46,
    LEFT = 65,
    RIGHT = 47,
    NONE = -1
};

// Helpers to work within joystick.c
int i2j(int joystickInd);
int j2i(enum Direction joystickDirection);
FILE *joystick_openGPIOFile(int dirNum, char *toOpen, char *perm);
void joystick_closeGPIOFile(FILE *GPIOFile);

// This is here because only joystick uses it at the moment, but with a different project should probably move it to utils
static void runCommand(char *command);

// Joystick initialization
void joystick_init(void);

// High-level user functions
bool joystick_isPressed(void);
enum Direction joystick_getCurrentDirection(void);

#endif