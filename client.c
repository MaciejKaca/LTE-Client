#include "Headers/common.h"

#include "Headers/connection.h"
#include "Headers/lte_attach.h"
#include "Headers/preambles.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

int client_socket;
UserEquipment user_equipment;
threadpool thread_pool;

extern void start_server_listening_thread();

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	if (argc < 3)
		error("Not enough arguments passed!");

	char *server_address = argv[1];
	int port = atoi(argv[2]);

	create_user_equipment();
	create_session(server_address, port);

	lte_attach();

	set_socket_non_blocking(client_socket);

	thread_pool = thpool_init(2);

	user_equipment.power_off_on_trigger();
	thpool_add_work(thread_pool, (void *)start_server_listening_thread, NULL);
	thpool_add_work(thread_pool, user_equipment.battery.battery_drain, NULL);

	thpool_wait(thread_pool);
	thpool_destroy(thread_pool);

	close(client_socket);
	return 0;
}