#pragma once

typedef enum Message_Type
{
	msg_random_access_preamble = 0,
	msg_random_access_response,
	msg_rrc_connection_request,
	msg_rrc_connection_setup,
	msg_rrc_connection_setup_complete,
	msg_ping_request,
	msg_ping_response,
	msg_ue_shutdown,
	msg_drx_config,
	msg_battery_critcal,
	msg_request_download,
	msg_download_info,
	msg_download_packet,
	msg_handover_request
} Message_Type;

typedef struct message_label
{
	Message_Type message_type;
	unsigned int message_length;
} message_label;
/*
printf("---File download started!---\n");
	for (int i = 0; i < download_info.number_of_packets; i++)
	{
		message_label label;
		Download_Packet packet;
		memset(&label, 0, sizeof(message_label));
		memset(&packet, 0, sizeof(Download_Packet));

		do
		{
			read(client_socket, (void *)&packet, sizeof(label));
		} while (label.message_type != msg_download_packet);

		read(client_socket, (void *)&packet, sizeof(packet));
		if (packet.packet_number == i)
			printf("Received packet %d/%d", i, download_info.number_of_packets);
		FILE *file = fopen(download_info.filename, "a");
		fprintf(file, "%s", packet.data);
	}
	printf("---File received!---\n");
	*/