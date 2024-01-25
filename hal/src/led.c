#include "hal/led.h"

FILE *led_openFile(int led_num, char *file_type)
{
    char path[sizeof(file_type)*strlen(file_type)];
    char loc[LED_BUF];
    snprintf(path, sizeof(path),"%d/%s",led_num,file_type);
    snprintf(loc,sizeof(loc),"%s%s",BBG_LED_DIR,path);

    FILE *file = fopen(loc,"w");

    if(file == NULL) {
        printf("ERROR: led_open_file: unable to open %s for %d\n",file_type,led_num);
        exit(1);
    }
    return file;
}

void led_close_file(FILE *led_file) {
    if(led_file)
    {
        fclose(led_file);
    }
}

void led_setTrigger(int led_num, char *state)
{

    FILE *trigger_file = led_openFile(led_num,"trigger");
    int set_trigger = fprintf(trigger_file, "%s", state);
    if(set_trigger <= 0) {
        printf("ERROR: led_setTrigger: Something went wrong in setting trigger.\n");
        exit(1);
    }
    led_close_file(trigger_file);

}

void led_setBrightness(int led_num, char *level)
{
    FILE *brightness_file = led_openFile(led_num,"brightness");

    int setBrightness = fprintf(brightness_file, "%s", level);
    if(setBrightness <= 0)
    {
        printf("ERROR: led_setBrightness: Something went wrong when modifying brightness.\n");
        exit(1);
    }
    led_close_file(brightness_file);
}
