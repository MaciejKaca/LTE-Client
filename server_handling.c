#include "Headers/server_handling.h"
#include "Headers/GUI/gui_logs.h"
#include "Headers/connection.h"
#include "Headers/download.h"
#include "Headers/handover.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern int client_socket;
extern UserEquipment user_equipment;
extern threadpool thread_pool;
extern int C_RNTI;
char available_file_list[64];

void resolve_ping()
{
	char ping_request[64];
	memset(&ping_request, 0, 64 * sizeof(char));

	read(client_socket, ping_request, 64 * sizeof(char));

	char ping_response[64];

	memset(&ping_response, 0, 64 * sizeof(char));

	message_label ping_response_label = {
		message_type : msg_ping_response,
		message_length : sizeof(ping_response)
	};

	send_data(client_socket, (void *)ping_response, ping_response_label);
	Ping_add_log_entry("PING sent.");
}

void resolve_available_file_list(int data_size)
{
	memset(available_file_list, 0, data_size);
	read(client_socket, available_file_list, data_size);

	for (int i = 0; i < data_size - 1; i++)
	{
		if (available_file_list[i] == '\0')
			available_file_list[i] = ',';
	}
}

void request_available_file_list()
{
	message_label label = {
		message_type : msg_request_available_file_list,
		message_length : 3
	};

	write(client_socket, (void *)&label, sizeof(message_label));

	user_equipment.is_requesting_file_list = false;
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

		if (response == 0)
			handle_connection_lost();

		usleep(50000);
		if (response == sizeof(message_label))
		{
			switch (label.message_type)
			{
			case msg_ping_request:
				Ping_add_log_entry("PING recived.");
				resolve_ping();
				break;
			case msg_download_info:
				resolve_download_info();
				break;
			case msg_download_packet:
				resolve_packet();
				break;
			case msg_x2_other_server_info:
				resolve_backup_server_info();
				break;
			case msg_handover_measurment_control:
				resolve_handover_control();
				break;
			case msg_handover_start:
				add_log_entry("X2 handover started.");
				resolve_handover_start();
				break;
			case msg_response_available_file_list:
				add_log_entry("Received available file list.");
				resolve_available_file_list(label.message_length);
				break;
			default:
				continue;
			}
		}
	}
}

void server_send_requests()
{
	if (user_equipment.is_requesting_download == true)
	{
		add_log_entry("Requested file download.");
		request_file_download();
	}

	if (user_equipment.is_requesting_file_list == true)
	{
		request_available_file_list();
	}
}

void server_handle_IO()
{
	while (user_equipment.battery.is_battery_drained() == false)
	{
		server_listen_respond();
		server_send_requests();

		user_equipment.is_sleeping = true;
		sleep(3);
		user_equipment.is_sleeping = false;
		sleep(1);
	}
}