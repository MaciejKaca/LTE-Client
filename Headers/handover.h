#pragma once

#include "common.h"
#include "lte_attach.h"
#include "user_equipment.h"
#include "connection.h"

#define ADDRESS_LENGTH 4

typedef unsigned char byte;

typedef struct X2_Server_Info {
    unsigned short eNodeB_port;
    byte address[ADDRESS_LENGTH];
}X2_Server_Info;

void resolve_backup_server_info();

void resolve_handover_control();

void resolve_handover_start();
