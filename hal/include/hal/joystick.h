/*
echo Up:
cat /sys/class/gpio/gpio26/value
echo Right:
cat /sys/class/gpio/gpio47/value
echo Down:
cat /sys/class/gpio/gpio46/value
echo Left:
cat /sys/class/gpio/gpio65/value
echo Push-button:
cat /sys/class/gpio/gpio27/value
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include<sys/mman.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

#define JOYSTICK_BUF 50
#define JOYSTICK_PATH "/sys/class/gpio/gpio"

enum Direction {
    UP = 26,
    DOWN = 46,
    RIGHT = 47,
    LEFT = 65,
    NONE = -1
};

struct Joystick {
    enum Direction direction;
};

void joystick_init();
FILE *joystick_openFile(int dir_num);
bool joystick_isPressed();

enum Direction joystick_getCurrentDirection();