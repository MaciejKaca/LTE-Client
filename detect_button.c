#include "Headers/detect_button.h"
extern UserEquipment user_equipment;
extern bool handover_response;
extern int client_socket;

void detect_button()
{
    int pressed_key;
    do
    {
        system("/bin/stty cbreak");
        pressed_key = getchar();
        switch (pressed_key)
        {
        case 'd':
            user_equipment.is_requesting_download = true;
            break;
        case 'h':
            user_equipment.signal_strength = 23;
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