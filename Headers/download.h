#pragma once

#include "common.h"
#include "connection.h"
#include "server_handling.h"
#include "user_equipment.h"
#include "GUI/gui_progress_bar.h"

#define ERR_DOWNLOAD_NO_ERRORS 0
#define ERR_DOWNLOAD_FILE_NOT_FOUND -1
#define DOWNLOAD_PACKET_SIZE 16

typedef struct Download_Request
{
	char filename[50];
	int client_C_RNTI;
} Download_Request;

typedef struct Download_Info
{
	char filename[50];
	int error_number;
	int number_of_packets;
} Download_Info;

typedef struct Download_Packet
{
	int packet_number;
	char data[DOWNLOAD_PACKET_SIZE];
	int data_size;
} Download_Packet;

void request_file_download();

void resolve_download_info();

void resolve_packet();