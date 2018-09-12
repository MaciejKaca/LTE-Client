#include "Headers/battery.h"
#include "Headers/common.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern UserEquipment user_equipment;
extern threadpool thread_pool;

void battery_drain()
{
	while (user_equipment.battery.is_battery_drained() == false)
	{
		if (!user_equipment.is_sleeping)
		{
			user_equipment.battery.charge -= 1;
			printf("Battery: %d%%\n", user_equipment.battery.charge);
			int time_before_battery_loss = (rand() % 600000) + 30000;
			usleep(time_before_battery_loss);
		}
	}

	printf("Battery drained. I hope you're proud of yourself.\n");
}

void battery_drain_start()
{
	thpool_add_work(thread_pool, (void *)battery_drain, NULL);
}

bool is_battery_critical() { return (user_equipment.battery.charge < 30); }

bool is_battery_drained() { return (user_equipment.battery.charge == 0); }

void create_battery()
{
	user_equipment.battery.charge = 100;
	user_equipment.battery.battery_drain = (void *)battery_drain;
	user_equipment.battery.battery_drain_start = (void *)battery_drain_start;
	user_equipment.battery.is_battery_critical = (void *)is_battery_critical;
	user_equipment.battery.is_battery_drained = (void *)is_battery_drained;
}