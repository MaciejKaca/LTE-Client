#include "Headers/common.h"

#include "Headers/connection.h"
#include "Headers/lte_attach.h"
#include "Headers/user_equipment.h"
#include "Headers/preambles.h"
#include <pthread.h>

int client_socket;
extern UserEquipment user_equipment;

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

	user_equipment.baterry.baterry_drain_start();

	close(client_socket);
	return 0;
}