#include "hal/joystick.h"

// Everything surrounding joystick functionality and I/O

static bool is_initialized = false;

// i2j, j2i: helper functions to convert from enums to array indices
// Not a fan of these as it is bad to scale for 8 directions, but for purpose of this game is alright
int i2j(int joystickInd)
{
    switch(joystickInd) {
        case 0:
            return UP;
        case 1:
            return DOWN;
        case 2:
            return RIGHT;
        case 3:
            return LEFT;
        default:
            return NONE;
    }
}

enum Direction j2i(enum Direction joystickDirection)
{
    switch(joystickDirection) {
        case UP:
            return 0;
        case DOWN:
            return 1;
        case RIGHT:
            return 2;
        case LEFT:
            return 3;
        default:
            return -1;
    }
}

// fopen() and fclose() functions with parsing and error-handling built in 
FILE *joystick_openGPIOFile(enum Direction direction, char *toOpen, char *perm)
{
    char loc[JOYSTICK_BUF];
    snprintf(loc,sizeof(loc),"%s%d/%s",JOYSTICK_PATH,direction,toOpen);

    // printf("%s",loc);

    FILE *file = fopen(loc,perm);

    if(file == NULL) {

        printf("ERROR: joystick_openFile: unable to open gpio%d. Check that the pin is exported\n",direction);
        exit(1);
    }
    return file;
}

void joystick_closeGPIOFile(FILE *file)
{
    if(file) {
        
        fclose(file);
    }
}

// Instructor provided code for running bash scripts from C
static void runCommand(char *command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");

    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if(fgets(buffer,sizeof(buffer),pipe) == NULL)
            break;
        // printf("--> %s", buffer); //Uncomment for debugging
    }

    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if(exitCode != 0) {
        perror("Unable to execute command:");
        printf("    command:    %s\n",command);
        printf("    exit code:  %d\n", exitCode);
    }
}

// Initialization: Make sure configurations are set and joystick directions set to "in"
void joystick_init()
{
    runCommand("~/config-pins.sh");
    // ensure that all joystick directions are set to "in"
    for(size_t i = 0; i < NUM_JOYSTICK_DIRECTIONS; i++) {

        FILE *cur = joystick_openGPIOFile(i2j(i),"direction", "w");
        fprintf(cur, "%s","in");
        joystick_closeGPIOFile(cur);
    }

    is_initialized = true;   
}

// if the joystick is pressed in any direction return true
bool joystick_isPressed()
{
    for(size_t i = 0; i < NUM_JOYSTICK_DIRECTIONS; i++) {

        FILE *cur = joystick_openGPIOFile(i2j(i),"value", "r");
        if(fgetc(cur)=='0') {

            joystick_closeGPIOFile(cur);
            return true;
        }
        joystick_closeGPIOFile(cur);
    }
    return false;
}
// If any, return the direction in which the joystick is pressed
enum Direction joystick_getCurrentDirection()
{
    if(!is_initialized) {

        printf("joystick module not initialized\n");
        exit(1);
    }

    for(size_t i = 0; i < NUM_JOYSTICK_DIRECTIONS; i++) {

        FILE *cur = joystick_openGPIOFile(i2j(i),"value", "r");
        if(fgetc(cur)=='0') {

            joystick_closeGPIOFile(cur);
            return i2j(i);
        }
        joystick_closeGPIOFile(cur);
    }

    return NONE;
}