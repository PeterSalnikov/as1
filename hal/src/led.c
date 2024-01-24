#include "hal/led.h"



struct LED *led_init()
{
    int buf = 50;
    struct LED *led = malloc(sizeof(struct LED) * NUM_LEDS);

    char bbg_led_path[37] = "/sys/class/leds/beaglebone:green:usr";

    for(int i = 0; i < NUM_LEDS; i++) {

        char trigger_path[10];
        char brightness_path[13];
        
        char trigger_loc[buf];
        char brightness_loc[buf];

        sprintf(trigger_path,"%d/trigger",i);
        snprintf(trigger_loc,sizeof(trigger_loc),"%s%s",bbg_led_path,trigger_path);

        sprintf(brightness_path,"%d/brightness",i);
        snprintf(brightness_loc,sizeof(brightness_loc),"%s%s",bbg_led_path,brightness_path);


        led[i].trigger = fopen(trigger_loc,"w");
        led[i].brightness = fopen(brightness_loc,"w");

    }

    return led;
}

void led_setTrigger(FILE *pLedTriggerFile, char *state)
{
    if(pLedTriggerFile == NULL) {
        printf("ERROR: led_setTrigger: FILE DOES NOT EXIST\n");
        exit(1);
    }

    int setTrigger = fprintf(pLedTriggerFile, "%s", state);
    if(setTrigger <= 0) {
        printf("ERROR: led_setTrigger: Something went wrong when modifying trigger.\n");
        exit(1);
    }
}

void led_setBrightness(FILE * pLedBrightnessFile, char *level)
{
    if(pLedBrightnessFile == NULL) {
        printf("ERROR: led_setBrightness: FILE DOES NOT EXIST\n");
        exit(1);
    }

    int setBrightness = fprintf(pLedBrightnessFile, "%s", level);
    if(setBrightness <= 0)
    {
        printf("ERROR: led_setBrightness: Something went wrong when modifying brightness.\n");
        exit(1);
    }
}

// void led_setTrigger(char *file, char *state)
// {
//     FILE *pLedTriggerFile = fopen(file, 'w');
//     if(pLedTriggerFile == NULL)
//     {
//         printf("ERROR OPENING %s.\n",file);
//         exit(1);
//     }
//     int charWritten = fprintf(pLedTriggerFile, "%s",state);
//     if(charWritten <= 0)
//     {
//         printf("ERROR WRITING DATA\n");
//         exit(1);
//     }
//     fclose(pLedTriggerFile);

// }


void led_cleanup()
{
    // if(led) {
    //     for(int i = 0; i < NUM_LEDS; i++) {
    //         fclose(led[i].trigger);
    //         fclose(led[i].brightness);
    //     }
    //     free(led);
    // }
}