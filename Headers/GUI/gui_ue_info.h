#pragma once

#include "../common.h"
#include "../user_equipment.h"

typedef struct GUI_UE_Info
{
	bool is_enabled;
	int x_position;
	int y_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_UE_Info;


GUI_UE_Info initialize_gui_ue_info();

void draw_ue_info_on_screen(char screen[23][80]);
