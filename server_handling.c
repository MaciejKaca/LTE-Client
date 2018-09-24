#include "Headers/server_handling.h"
#include "Headers/connection.h"
#include "Headers/download.h"
#include "Headers/handover.h"
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
}

void resolve_backup_server_info()
{
	read(client_socket, (void *)&user_equipment.backup_server_info,
		 sizeof(user_equipment.backup_server_info));
	char backup_server_ip[4];
	strncpy(backup_server_ip, user_equipment.backup_server_info.address, 4);

	printf("Backup server received: %d.%d.%d.%d:%d\n", backup_server_ip[0],
		   backup_server_ip[1], backup_server_ip[2], backup_server_ip[3],
		   user_equipment.backup_server_info.eNodeB_port);
}

void resolve_handover_control()
{
	void *trash_buffer = malloc(1);
	read(client_socket, trash_buffer, sizeof(byte));
	free(trash_buffer);

	message_label measurment_report_label = {
		message_type : msg_handover_measurment_report,
		message_length : sizeof(user_equipment.signal_strength)
	};
	send_data(client_socket, &user_equipment.signal_strength,
			  measurment_report_label);
}

void resolve_handover_start() {}

void server_listen_respond()
{
	message_label label;
	memset(&label, 0, sizeof(message_label));

	while (true)
	{
		int response =
			read(client_socket, (void *)&label, sizeof(message_label));
		printf("RESPONSE: %d\n",response);
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
				break;
			case msg_download_packet:
				print_received_data_type("msg_download_packet");
				resolve_packet();
				break;
			case msg_x2_other_server_info:
				print_received_data_type("msg_x2_other_server_info");
				resolve_backup_server_info();
				break;
			case msg_handover_measurment_control:
				print_received_data_type("msg_handover_measurment_control");
				resolve_handover_control();
				break;
			case msg_handover_start:
				print_received_data_type("msg_handover_start");
				resolve_handover_start();
				break;
			default:
				printf("Unknown message type. ID=%d\n", label.message_type);
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
		// printf("---Device goes to sleep.---\n");
		sleep(4);
		// printf("\n---Device wakes up!---\n");
		usleep(100000);
		user_equipment.is_sleeping = false;
		sleep(1);
	}

	printf("Listening stopped.\n");
}