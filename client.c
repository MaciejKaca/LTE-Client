#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 

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
	if (argc < 3) {
		error("Not enough arguments passed!");
		exit(0);
	}

	char *server_address = argv[1];
	int port = atoi(argv[2]);

	create_session(server_address, port);
	
	struct RandomAccessPreamble rap;
	rap.cyclic_prefix='z';
	write(client_socket,(void*)&rap,sizeof(rap));
	lte_attach();

	return 0;
}