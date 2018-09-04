#include "Headers/common.h"

#include "Headers/preambles.h"
#include "Headers/lte_attach.h"
#include "Headers/connection.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int client_socket;

int main(int argc, char *argv[])
{
	srand((unsigned)time(NULL));
	if (argc < 3)
		error("Not enough arguments passed!");

	char *server_address = argv[1];
	int port = atoi(argv[2]);

	create_session(server_address, port);
	lte_attach();

	return 0;
}