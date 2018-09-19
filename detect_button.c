#include "Headers/detect_button.h"
extern UserEquipment user_equipment;
extern bool handover_response;
extern int client_socket;

void detect_button()
{
    int pressed_key;
    bool handover_sended = false;
    char handover_msg[] = "handover_request";
    message_label handover_label = {
        message_type : msg_handover_request,
        message_length : sizeof(handover_msg)
    };
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
            if(handover_sended == false)
            {
                send_data(client_socket, (void *)handover_msg, handover_label);
                print_sent_data_type("msg_handover_request");
            }
            handover_sended = true;
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