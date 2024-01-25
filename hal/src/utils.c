#include "../include/utils.h"
#include "hal/joystick.h"

double random_wait(double min, double max)
{
    return ((double)rand() / (double)RAND_MAX) * (max - min) + min;
}

int random_upDown()
{
    return i2j(rand() % 2);
}

int min(int a, int b)
{
    return (a < b) ? a : b;
}