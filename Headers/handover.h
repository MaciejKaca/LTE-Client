#pragma once

#include "common.h"
#include "connection.h"
#include "lte_attach.h"
#include "user_equipment.h"

#define ADDRESS_LENGTH 4

typedef unsigned char byte;

typedef struct X2_Server_Info
{
	unsigned short eNodeB_port;
	byte address[ADDRESS_LENGTH];
} X2_Server_Info;

void reconnect_to_backup_server();

void handle_connection_lost();

void resolve_backup_server_info();

void resolve_handover_control();

void resolve_handover_start();
