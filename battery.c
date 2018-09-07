#include "Headers/common.h"
#include "Headers/battery.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern UserEquipment user_equipment;

void *battery_drain()
{
    while (true)
    {
        user_equipment.battery.charge -= 1;
        printf("battery: %d%%\n", user_equipment.battery.charge);
        sleep(2);
    }
}

void *battery_drain_start()
{
    pthread_t battery_drain_thread, test;
    pthread_create(&battery_drain_thread, NULL, battery_drain, NULL);
    pthread_join(battery_drain_thread, NULL);
}

bool *is_battery_charged()
{
    return user_equipment.battery.charge > 0;
}

void create_battery()
{
    user_equipment.battery.charge = 100;
    user_equipment.battery.battery_drain = battery_drain;
    user_equipment.battery.battery_drain_start = battery_drain_start;
}