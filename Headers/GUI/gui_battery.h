#pragma once

#include "../common.h"
#include "../user_equipment.h"

typedef struct GUI_Battery
{
	bool is_enabled;
	int x_position;
	int y_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_Battery;


GUI_Battery initialize_gui_battery();
