#include "Headers/common.h"
#include "Headers/connection.h"
#include "Headers/lte_attach.h"
#include "Headers/preambles.h"
#include "Headers/user_equipment.h"
#include "Headers/listen_to_server.h"
#include "Headers/threading.h"
#include <pthread.h>

int client_socket;
UserEquipment user_equipment;

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
	create_thread_pool();

	close(client_socket);
	return 0;
}