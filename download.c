#include "Headers/download.h"

extern int client_socket;
extern int C_RNTI;
extern UserEquipment user_equipment;
extern GUI_ProgressBar gui_progress_bar;
Download_Info download_info;
int current_packet_number;

void request_file_download()
{
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

void resolve_download_info()
{
	memset(&download_info, 0, sizeof(Download_Info));
	read(client_socket, (void *)&download_info, sizeof(download_info));

	FILE *file = fopen(download_info.filename, "w");
	fclose(file);
}

void resolve_packet()
{
	Download_Packet packet;
	memset(&packet, 0, sizeof(Download_Packet));

	read(client_socket, (void *)&packet, sizeof(packet));

	current_packet_number = packet.packet_number + 1;

	FILE *file = fopen(download_info.filename, "a");
	fprintf(file, "%.*s", packet.data_size, packet.data);
	fflush(file);
	fclose(file);
}