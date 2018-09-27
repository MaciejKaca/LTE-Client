#pragma once

#include "../common.h"
#include "../queue.h"
#include "../user_equipment.h"
#include "gui_helper.h"

typedef struct GUI_Logs
{
	bool is_enabled;
	int x_position;
	int y_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_Logs;


GUI_Logs initialize_gui_logs();

void draw_logs_on_screen(char screen[23][80]);
