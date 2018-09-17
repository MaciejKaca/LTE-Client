#include "Headers/detect_button.h"

extern UserEquipment user_equipment;
extern bool handover_response;

void detect_button()
{
    int c;
    do
    {
        system("/bin/stty cbreak");
        c = getchar();
        switch (c)
        {
        case 'a':
            user_equipment.is_requesting_download = true;
            break;
        case 'h':
            handover_response = true;
            break;
        default:
            printf("------------------------\n");
            printf("Undefinied button\n");
            printf("------------------------\n");
        }
        system("/bin/stty -cbreak");
    } while (true);

    printf("Keyboard stodofdf\n");
}