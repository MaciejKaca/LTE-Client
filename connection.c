#include "Headers/connection.h"

extern UserEquipment user_equipment;
extern int client_socket;

void create_session(char *server_addres, int port)
{
	sprintf(user_equipment.eNodeB.ip, "%s", server_addres);
	user_equipment.eNodeB.port = port;
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

	if (connect(client_socket, (struct sockaddr *)&serv_addr,
				sizeof(serv_addr)) < 0)
		error("Connection failed!");
}

void set_socket_non_blocking(int socket)
{
	int flags = fcntl(socket, F_GETFL, 0);
	fcntl(socket, F_SETFL, flags | O_NONBLOCK);
}

int send_data(int socket, void *data, message_label label)
{
	int result;

	result = write(socket, (void *)&label, sizeof(message_label));
	if (result < 0)
		error("Couldn't write to the socket.");

	result = write(socket, data, label.message_length);
	if (result < 0)
		error("Couldn't write to the socket.");

	return result;
}

int read_data_blocking(int socket, void *data, int data_size)
{
	int result = 0;

	while (result != data_size)
		result = read(socket, data, data_size);

	return result;
}

int recive_data_blocking(int socket, void *data, message_label *label)
{
	int result;
	while (true)
	{
		result =
			read_data_blocking(socket, (void *)label, sizeof(message_label));

		usleep(50000);

		if (result == sizeof(message_label))
		{
			switch (label->message_type)
			{
			case msg_random_access_response:
				return read_data_blocking(socket, data, label->message_length);
				break;
			case msg_rrc_connection_setup:
				return read_data_blocking(socket, data, label->message_length);
				break;
			case msg_handover_client_reconnection_info:
				return read_data_blocking(socket, data, label->message_length);
				break;
			default:
				continue;
				break;
			}
			break;
		}
		else
			continue;
	}
}
