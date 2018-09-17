#include "Headers/server_handling.h"
#include "Headers/connection.h"
#include "Headers/download.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern int client_socket;
extern UserEquipment user_equipment;
extern threadpool thread_pool;
extern int C_RNTI;

Download_Info download_info;

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

void resolve_download_info()
{
	memset(&download_info, 0, sizeof(Download_Info));	
	read(client_socket, (void *)&download_info, sizeof(download_info));

	printf("------------------------------------------\n");
	printf("DOWNLOAD INFO\n");
	printf("Filename: %s\n", download_info.filename);
	printf("Download ID: %d\n", download_info.error_number);
	printf("Number of packets: %d\n", download_info.number_of_packets);
	printf("------------------------------------------\n");
}

void resolve_packet()
{
	Download_Packet packet;
	memset(&packet, 0, sizeof(Download_Packet));

	read(client_socket, (void *)&packet, sizeof(packet));

	printf("Received packet %d/%d\n", ++packet.packet_number, download_info.number_of_packets);
	printf("Data: %s\n", packet.data);

	FILE *file = fopen(download_info.filename, "a");
	fprintf(file, "%s", packet.data);
	fflush(file);
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

void request_file_download()
{
	print_sent_data_type("msg_download_request");
	Download_Request file_download_request = {
		filename : "file.txt",
		client_C_RNTI : C_RNTI
	};
	message_label file_download_request_label = {
		message_type : msg_request_download,
		message_length : sizeof(file_download_request)
	};
	send_data(client_socket, (void *)&file_download_request,
			  file_download_request_label);

	user_equipment.is_requesting_download = false;
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