#include "Headers/server_handling.h"
#include "Headers/connection.h"
#include "Headers/download.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern int client_socket;
extern UserEquipment user_equipment;
extern threadpool thread_pool;
extern int C_RNTI;

void print_received_data_type(char message[])
{
	printf("------------------------------------------\n");
	printf("RECEIVED MESSAGE\n");
	printf("Type: %s\n", message);
	printf("------------------------------------------\n");
}

void print_sent_data_type(char message[])
{
	printf("------------------------------------------\n");
	printf("SENT MESSAGE\n");
	printf("Type: %s\n", message);
	printf("------------------------------------------\n");
}

void resolve_ping()
{
	char ping_response[64];

	memset(&ping_response, 0, 64*sizeof(char));


	message_label ping_response_label = {
		message_type : msg_ping_response,
		message_length : sizeof(ping_response)
	};

	send_data(client_socket, (void *)&ping_response, ping_response_label);
}

void server_listen_respond()
{
	message_label label;
	memset(&label, 0, sizeof(message_label));

	while (true)
	{
		int response =
			read(client_socket, (void *)&label, sizeof(message_label));
		if (response < 0)
			break;
		usleep(50000);
		if (response == sizeof(message_label))
		{
			switch (label.message_type)
			{
			case msg_ping_request:
				print_received_data_type("msg_ping_request");
				resolve_ping();
				break;
			case msg_download_info:
				print_received_data_type("msg_download_info");
				resolve_download_info();
			case msg_download_packet:
				print_received_data_type("msg_download_packet");
				resolve_packet();
				break;
			case msg_handover_request:
				print_received_data_type("msg_handover_request");
				break;
			default:
				//printf("Unknown message type.\n");
				continue;
			}
		}
	}
}

void server_send_requests()
{
	if (user_equipment.is_requesting_download == true)
		request_file_download();
}

void server_handle_IO()
{
	while (user_equipment.battery.is_battery_drained() == false)
	{
		server_listen_respond();
		server_send_requests();

		user_equipment.is_sleeping = true;
		//printf("---Device goes to sleep.---\n");
		sleep(4);
		//printf("\n---Device wakes up!---\n");
		usleep(100000);
		user_equipment.is_sleeping = false;
		sleep(1);
	}

	printf("Listening stopped.\n");
}