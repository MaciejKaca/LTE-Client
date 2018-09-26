#include "Headers/detect_button.h"
extern UserEquipment user_equipment;
extern bool handover_response;
extern int client_socket;
extern GUI_ProgressBar gui_progress_bar;

extern char requested_file_name[50];

void detect_button()
{
	char key_stack[50];
	int key_stack_iter = 0;
	bool is_user_typing_filename = false;

	int pressed_key;
	do
	{
		system("/bin/stty cbreak");
		
		pressed_key = getchar();

		if(is_user_typing_filename == true && pressed_key != 10)
		{
			key_stack[key_stack_iter] = pressed_key;
			key_stack_iter++;
		}

		switch (pressed_key)
		{
		case '1':
			memset(&key_stack, 0, sizeof(key_stack));
			is_user_typing_filename = true;
			break;
		case '2':
			user_equipment.signal_strength = 23;
			break;
		case 10:
			if(is_user_typing_filename == true)
			{
				key_stack[key_stack_iter+1] = '\0';
				strcpy(requested_file_name, key_stack);
				user_equipment.is_requesting_download = true;
				gui_progress_bar.is_enabled = true;
				is_user_typing_filename = false;
				key_stack_iter = 0;
			}
			break;	
		default:
			break;
		}

		system("/bin/stty -cbreak");
	} while (true);
	printf("Keyboard stodofdf\n");
}