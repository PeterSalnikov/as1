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

enum Direction {
    UP = 26,
    DOWN = 46,
    LEFT = 65,
    RIGHT = 47,
    NONE = -1
};

struct Joystick {
    enum Direction direction;
};