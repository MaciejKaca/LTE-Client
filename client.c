#include "preambles.h"
#include "lte_attach.h"
#include "connection.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int client_socket;

int main(int argc, char *argv[])
{
	if (argc < 3) {
		error("Not enough arguments passed!");
		exit(0);
	}

	create_session(argv);
	lte_attach();

	return 0;
}