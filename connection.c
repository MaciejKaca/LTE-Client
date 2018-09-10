#include "Headers/connection.h"
#include "Headers/preambles.h"
#include "Headers/rrc_connection.h"

void create_session(char *server_addres, int port)
{
	create_socket();
	connect_to_server(server_addres, port);
}

void create_socket()
{
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket < 0)
		error("Can't open socket!");
}

void connect_to_server(char *server_addres, int port)
{
	struct sockaddr_in serv_addr;
	struct hostent *server;

	server = gethostbyname(server_addres);
	if (server == NULL)
		error("No such host!");

	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	bcopy((char *)server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr,
		  server->h_length);
	serv_addr.sin_port = htons(port);

	if (connect(client_socket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <
		0)
		error("Connection failed!");
}

void set_socket_non_blocking(int socket)
{
	int flags = fcntl(socket, F_GETFL, 0);
	fcntl(socket, F_SETFL, flags | O_NONBLOCK);
}

void send_data(int socket, void *data, int data_size, message_label *label)
{
	int result;
	result = write(socket, (void *)label, sizeof(message_label));

	if (result < 0)
		error("Couldn't write to the socket.");
	else
		printf("Data sent successfully.\n");

	result = write(socket, data, data_size);

	if (result < 0)
		error("Couldn't write to the socket.");
	else
		printf("Data sent successfully.\n");
}

char *read_data(int socket, int data_size)
{
	char *buffer = malloc(data_size);
	bzero(buffer, data_size);
	int result = read(socket, buffer, data_size);

	if (result < 0)
		error("Can't read from the socket.\n");

	return buffer;
}

char *receive_data(int socket)
{
	message_label label;

	int result = read(socket, (void *)&label, sizeof(label));

	while(true)
	{
		if (result == sizeof(message_label))
		{
			switch (label.message_type)
			{
			case msg_random_access_response:
				return read_data(socket, label.message_length);
				break;
			case msg_rrc_connection_setup:
				return read_data(socket, label.message_length);
				break;
			case msg_ping_response:
				return read_data(socket, label.message_length);
				break;
			default:
				return "XDDDD\n";
				break;
			}
			break;
		}
		else if (result < (int)sizeof(message_label))
		{
			printf("Wrong data received.\n");
			continue;			
		}
		else
		{
			printf("Can't read from the socket.\n");
			continue;
		}
	}
		
}
