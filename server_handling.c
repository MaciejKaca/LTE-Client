#include "Headers/server_handling.h"
#include "Headers/connection.h"
#include "Headers/download.h"
#include "Headers/user_equipment.h"
#include <pthread.h>

extern int client_socket;
extern UserEquipment user_equipment;
extern threadpool thread_pool;
extern int C_RNTI;

void resolve_ping(bool ping_already_sent)
{
	char ping_response[64];
	char ping_request[64];

	memset(&ping_response, 0, 64*sizeof(char));
	memset(&ping_request, 0, 64*sizeof(char));

	message_label ping_response_label = {
		message_type : msg_ping_response,
		message_length : sizeof(ping_response)
	};

	read(client_socket, (void *)ping_request, sizeof(ping_request));
	printf("------------------------------------------\n");
	printf("RECEIVED MESSAGE\n");
	printf("Type: msg_ping_request\n");
	printf("------------------------------------------\n");
	if (!ping_already_sent)
		send_data(client_socket, (void *)&ping_response, ping_response_label);
}

void server_listen_respond()
{
	message_label label;
	memset(&label, 0, sizeof(message_label));
	bool ping_sent = false;
	
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
				resolve_ping(ping_sent);
				ping_sent = true;
				break;
			default:
				printf("Unknown message type.\n");
				continue;
			}
		}
	}
}

void server_send_requests() 
{ 
	if(user_equipment.is_requesting_download == true)
    	download_file(); 
}

void download_file()
{
	printf("---Sending request for file download.---\n");
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

	message_label label;
	memset(&label, 0, sizeof(message_label));

	do
	{
		read(client_socket, (void*)&label, sizeof(label));
	} while (label.message_type != msg_download_info);

    Download_Info download_info;
	memset(&download_info, 0, sizeof(Download_Info));
    read(client_socket,(void*)&download_info,sizeof(download_info));

	printf("---File download started!---\n");
    for(int i=0;i<download_info.number_of_packets;i++)
    {
	    message_label label;
        Download_Packet packet;
		memset(&label, 0, sizeof(message_label));
		memset(&packet, 0, sizeof(Download_Packet));

        do
        {
            read(client_socket,(void*)&packet,sizeof(label));
        } while(label.message_type != msg_download_packet);

        read(client_socket,(void*)&packet,sizeof(packet));
        if(packet.packet_number == i)
			printf("Received packet %d/%d",i,download_info.number_of_packets);
		FILE *file = fopen(download_info.filename,"a");
		fprintf(file,"%s",packet.data);
    }
	printf("---File received!---\n");
}

void server_handle_IO()
{
	while (user_equipment.battery.is_battery_drained() == false)
	{
		server_listen_respond();
		server_send_requests();

		user_equipment.is_sleeping = true;
		printf("---Device goes to sleep.---\n");
		sleep(4);
		printf("\n---Device wakes up!---\n");
		usleep(100000);
		user_equipment.is_sleeping = false;
		sleep(1);
	}

	printf("Listening stopped.\n");
}