#include "Headers/detect_button.h"

extern UserEquipment user_equipment;

void detect_button()
{

    int c;
    do
    {
        system("/bin/stty cbreak"); 
        c = getchar();
        if (c == 'a')
            user_equipment.is_requesting_download = true;
        system("/bin/stty -cbreak");
    } while (user_equipment.battery.is_battery_drained() == false);

    printf("Keyboard stodofdf\n");
}