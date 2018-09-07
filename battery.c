#include "Headers/common.h"
#include "Headers/battery.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern UserEquipment user_equipment;

typedef struct BatteryArgs
{
    int battery_drain_value;
    int delay;
} BatteryArgs;

void *battery_drain(BatteryArgs *arguments)
{
    int delay = arguments->delay;
    int battery_dain_value = arguments->battery_drain_value;
    while (true)
    {
        user_equipment.baterry.charge -= battery_dain_value;
        sleep(delay);
        printf("Battery_drain\n");
    }
}

void *battery_drain_start(int battery_drain_value, int delay)
{
    struct BatteryArgs battery_args;
    battery_args.battery_drain_value = battery_drain_value;
    battery_args.delay = delay;

    pthread_t battery_drain_thread;
    pthread_create(&battery_drain_thread, NULL, battery_drain, (void *)&battery_args);
    pthread_join(battery_drain_thread, NULL);
}

void create_battery()
{
    user_equipment.baterry.charge = 100;
    user_equipment.baterry.battery_drain = battery_drain;
    user_equipment.baterry.baterry_drain_start = battery_drain_start;
}