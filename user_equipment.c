#include "Headers/user_equipment.h"

UserEquipment user_equipment;

void create_user_equipment_imsi()
{
    strcat(user_equipment.imsi, user_equipment.mmc);
    strcat(user_equipment.imsi, user_equipment.mnc);
    strcat(user_equipment.imsi, user_equipment.msin);
}

void create_user_equipment_plmn()
{
    strncpy(user_equipment.plmn, user_equipment.mmc, 7);
    strcat(user_equipment.plmn, user_equipment.mnc);
}

UserEquipment create_user_equipment()
{
    strncpy(user_equipment.mmc, "260", 3);
    strncpy(user_equipment.mnc, "06", 2);
    strncpy(user_equipment.msin, "123456789", 9);

    create_user_equipment_plmn();
    create_user_equipment_imsi();
}