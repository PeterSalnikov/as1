#include "hal/led.h"

// static bool is_initialized = false;

struct LED led_init()
{
    int buf = 50;
    struct LED led[1];
    // struct LED led = NULL;
    char bbg_led_path[37] = "/sys/class/leds/beaglebone:green:usr";


    char trigger_path[10];
    char brightness_path[13];
    
    char trigger_loc[buf];
    char brightness_loc[buf];

    sprintf(trigger_path,"%d/trigger",0);
    snprintf(trigger_loc,sizeof(trigger_loc),"%s%s",bbg_led_path,trigger_path);

    sprintf(brightness_path,"%d/brightness",0);
    snprintf(brightness_loc,sizeof(brightness_loc),"%s%s",bbg_led_path,brightness_path);


    led[0].trigger = fopen(trigger_loc,"w");
    led[0].brightness = fopen(brightness_loc,"w");


    return *led;
}

// void led_cleanup(struct LED *led)
// {
//     // if(led) {
//     //     for(int i = 0; i < NUM_LEDS; i++) {
//     //         fclose(led[i].trigger);
//     //         // fclose(led[i].brightness);
//     //     }
//     //     free(led);
//     // }
// }