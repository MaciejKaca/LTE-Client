#pragma once

#include "common.h"

typedef struct Baterry
{
    int charge;

    // TODO:
    //      - implement thread that regulary drains baterry
    //      - implement function that drains baterry by certain amount when called
    //      - eat flan
} Baterry;

typedef struct UserEquipment
{
    char mmc[4];   // Mobile Country Code
    char mnc[3];   // Mobile Network Code
    char msin[10]; // Mobile Subscriber Identification Number
    char imsi[16]; // International Mobile Subscriber Identity
    char plmn[8];

    Baterry baterry;
} UserEquipment;

void create_user_equipment_imsi();
void create_user_equipment_plmn();

UserEquipment create_user_equipment();
