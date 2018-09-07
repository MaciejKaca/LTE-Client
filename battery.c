#include "Headers/common.h"
#include "Headers/battery.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern UserEquipment user_equipment;

void *battery_drain()
{
    while (true)
    {
        user_equipment.baterry.charge -= 1;
        sleep(2);
        printf("Battery_drain\n");
    }
}

void *battery_drain_start()
{
    pthread_t battery_drain_thread, test;
    pthread_create(&battery_drain_thread, NULL, battery_drain, NULL);
    pthread_join(battery_drain_thread, NULL);
}

void create_battery()
{
    user_equipment.baterry.charge = 100;
    user_equipment.baterry.battery_drain = battery_drain;
    user_equipment.baterry.baterry_drain_start = battery_drain_start;
}