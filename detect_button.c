#include "Headers/detect_button.h"
extern UserEquipment user_equipment;
extern bool handover_response;
extern int client_socket;

extern GUI_ProgressBar gui_progress_bar;

void detect_button()
{
	int pressed_key;
	do
	{
		system("/bin/stty cbreak");
		pressed_key = getchar();
		switch (pressed_key)
		{
		case 112: //F1
			user_equipment.is_requesting_download = true;	
			gui_progress_bar.is_enabled = true;
			break;
		case 113: //F2
			user_equipment.signal_strength = 23;
			break;
		default:
			break;
		}
		system("/bin/stty -cbreak");
	} while (true);

	printf("Keyboard stodofdf\n");
}