#include "Headers/error.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}