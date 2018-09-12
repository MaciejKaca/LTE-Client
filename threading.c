#include "Headers/threading.h"

extern UserEquipment user_equipment;
threadpool thread_pool;

extern void listen_to_server();

void create_thread_pool()
{
    thread_pool = thpool_init(2);

	user_equipment.power_off_on_trigger();
	thpool_add_work(thread_pool, (void *)listen_to_server, NULL);
	thpool_add_work(thread_pool, user_equipment.battery.battery_drain, NULL);

	thpool_wait(thread_pool);
	thpool_destroy(thread_pool);
}