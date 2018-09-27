#include "Headers/detect_button.h"
#include "Headers/GUI/gui_logs.h"
extern UserEquipment user_equipment;
extern bool handover_response;
extern int client_socket;
extern GUI_ProgressBar gui_progress_bar;
extern GUI_AvailableFileList gui_available_file_list;
extern char requested_file_name[50];
extern bool is_user_typing_filename = false;
char key_stack[50];

void detect_button()
{	
	memset(&key_stack, 0, sizeof(key_stack));
	int key_stack_iter = 0;
	
	int pressed_key;
	do
	{ 
		system("/bin/stty cbreak");
		
		pressed_key = getchar();

		if(is_user_typing_filename)
		{
			switch(pressed_key)
			{
			case 10: // enter
				if(is_user_typing_filename)
				{
					key_stack[key_stack_iter+1] = '\0';
					strcpy(requested_file_name, key_stack);
					user_equipment.is_requesting_download = true;
					gui_progress_bar.is_enabled = true;
					is_user_typing_filename = false;
					key_stack_iter = 0;
					memset(&key_stack, 0, sizeof(key_stack));
				}
			break;	
			case 127: // backspace
				if(is_user_typing_filename)
				{
					key_stack_iter--;
					key_stack[key_stack_iter] = '\0';
				}
			break;
			default:
				key_stack[key_stack_iter] = pressed_key;
				key_stack_iter++;
			break;
			}	
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
		case '3':
			user_equipment.is_requesting_file_list = true;
			gui_available_file_list.is_enabled = true;
			break;
		default:
			break;
		}
		system("/bin/stty -cbreak");
	} while (true);
	printf("Keyboard stodofdf\n");
}