#pragma once

#include "battery.h"
#include "common.h"
#include "handover.h"

typedef struct UserEquipment
{
	char mmc[4];   // Mobile Country Code
	char mnc[3];   // Mobile Network Code
	char msin[10]; // Mobile Subscriber Identification Number
	char imsi[16]; // International Mobile Subscriber Identity
	char plmn[8];
	int signal_strength;
	bool is_sleeping;
	bool is_requesting_download;
	void (*power_off_on_trigger)();
	Battery battery;
	X2_Server_Info backup_server_info;
} UserEquipment;

void create_user_equipment_imsi();
void create_user_equipment_plmn();

UserEquipment create_user_equipment();
