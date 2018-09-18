#include "Headers/common.h"
#include "Headers/connection.h"
#include "Headers/lte_attach.h"
#include "Headers/preambles.h"
#include "Headers/user_equipment.h"
#include "Headers/server_handling.h"
#include "Headers/threading.h"
#include "Headers/detect_button.h"
#include <pthread.h>

int client_socket;
UserEquipment user_equipment;
bool test_mode = false;

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	if (argc == 3)
		error("Not enough arguments passed!");
	else if (argc == 4)
		test_mode = argv[3];

	char *server_address = argv[1];
	int port = atoi(argv[2]);

	create_user_equipment();
	create_session(server_address, port);
	lte_attach();
	set_socket_non_blocking(client_socket);
	create_thread_pool();

	close(client_socket);
	return 0;
}