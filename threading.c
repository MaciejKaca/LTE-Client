#include "Headers/threading.h"

#define THREADS_NUM 3

extern UserEquipment user_equipment;
extern bool test_mode;
threadpool thread_pool;

extern void server_handle_IO();

void create_thread_pool()
{
    thread_pool = thpool_init(THREADS_NUM);

	user_equipment.power_off_on_trigger();
	thpool_add_work(thread_pool, (void *)server_handle_IO, NULL);
	thpool_add_work(thread_pool, user_equipment.battery.battery_drain, NULL);
	
	if(test_mode == false)
		thpool_add_work(thread_pool, detect_button, NULL);
	
	thpool_wait(thread_pool);
	thpool_destroy(thread_pool);
}