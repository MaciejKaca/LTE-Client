#include "Headers/error.h"

extern client_socket;

void error(char *msg)
{
	errno = ECANCELED;
	perror(msg);
	close(client_socket);
	exit(EXIT_FAILURE);
}