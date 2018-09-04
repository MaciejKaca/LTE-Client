#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "connection.h"

void create_session(char *arguments[])
{
    create_socket();
    connect_to_server(arguments);
}

void create_socket()
{
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0)
		error("ERROR opening socket");
}

void connect_to_server(int *arguments[])
{
	struct sockaddr_in serv_addr;
	struct hostent *server; 

	int port = arguments[2];

	server = gethostbyname(arguments[1]);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host!\n");
		exit(0);
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char *) server->h_addr_list[0], (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    if (connect(client_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
        error("Connection failed!");   
}