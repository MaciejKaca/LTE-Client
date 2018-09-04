#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "preambles.h"
#include "lte_attach.h"

void error(char *msg)
{
	perror(msg);
	exit(0);
}

int client_socket, port;

void create_socket()
{
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
}

void connect_to_server(int *arguments[])
{
	struct sockaddr_in serv_addr;
	struct hostent *server; 

	port = arguments[2];

	server = gethostbyname(arguments[1]);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host!\n");
		exit(0);
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);

	if (connect(sockfd, &serv_addr, sizeof(serv_addr)) < 0)
		error("Connection failed!");
}

int main(int argc, char *argv[])
{
	if (argc < 3) {
		fprintf(stderr, "Not enough arguments passed!", argv[0]);
		exit(0);
	}

	create_socket();
	connect_to_server(argv);
	lte_attach();

	return 0;
}