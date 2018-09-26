#pragma once

#include "../common.h"

typedef struct GUI_C_RNTI
{
	bool is_enabled;
	int x_position;
	int y_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_C_RNTI;


GUI_C_RNTI initialize_gui_c_rtni();

void draw_c_rnti_on_screen(char screen[23][80]);
