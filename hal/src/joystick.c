#include "hal/joystick.h"

static bool is_initialized = false;

int i2j(int joystick_ind)
{
    switch(joystick_ind){
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

enum Direction j2i(int joystick_ind)
{
    switch(joystick_ind)
    {
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

// configure all joystick pin's direction to be "in"
void joystick_initDirection() 
{
    for(int i = 0; i < 4; i++) {
        FILE *cur = joystick_openGPIOFile(i2j(i),"direction", "w");
        fprintf(cur, "%s","in");
        joystick_closeGPIOFile(cur);
    }
}

void joystick_init()
{
    // I tried mmaps. I think I got close but in the interest of time will
    // hold off on using them here. I think all that I needed for them to work was
    // the location of the starting addresses of the respective GPIO pins as
    // they could not be found. I believe that these are located in Derek Molloy's BBG GPIO schematic?
    // runCommand("/home/debian/config-pins.sh");
    runCommand("~/config-pins.sh");
    joystick_initDirection();


    is_initialized = true;   
}


bool joystick_isPressed()
{
    for(int i = 0; i < 4; i++) {
        FILE *cur = joystick_openGPIOFile(i2j(i),"value", "r");
        if(fgetc(cur)=='0') {
            joystick_closeGPIOFile(cur);
            return true;
        }
        joystick_closeGPIOFile(cur);
    }
    return false;
}

enum Direction joystick_getCurrentDirection()
{
    if(!is_initialized) {
        printf("joystick module not initialized\n");
        exit(1);
    }

    for(int i = 0; i < 4; i++) {
        FILE *cur = joystick_openGPIOFile(i2j(i),"value", "r");
        if(fgetc(cur)=='0') {
            joystick_closeGPIOFile(cur);
            return i2j(i);
        }
        joystick_closeGPIOFile(cur);
    }

    return NONE;
}