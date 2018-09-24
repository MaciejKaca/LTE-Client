#include "Headers/download.h"

extern int client_socket;
extern UserEquipment user_equipment;
extern int C_RNTI;
Download_Info download_info;

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

	FILE *file = fopen(download_info.filename, "w");
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

	printf("Received packet %d/%d\n", ++packet.packet_number,
		   download_info.number_of_packets);
	printf("Data: %.*s\n", packet.data_size, packet.data);

	FILE *file = fopen(download_info.filename, "a");
	fprintf(file, "%.*s", packet.data_size, packet.data);
	fflush(file);
}