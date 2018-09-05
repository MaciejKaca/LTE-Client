#include "Headers/error.h"

void error(char *msg)
{
	errno = ECANCELED;
	perror(msg);
	exit(EXIT_FAILURE);
}