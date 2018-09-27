#pragma once

#include "../common.h"
#include "../user_equipment.h"
#include "gui_helper.h"

typedef struct GUI_AvailableFileList
{
	bool is_enabled;
	int x_position;
	int y_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_AvailableFileList;


GUI_AvailableFileList initialize_available_file_list();

void draw_available_file_list_on_screen(char screen[23][80]);
