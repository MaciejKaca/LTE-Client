#pragma once

#include "../common.h"

typedef struct GUI_Menu
{
	bool is_enabled;
	int x_position;
	int y_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_Menu;


GUI_Menu initialize_gui_menu();

void draw_menu_on_screen(char screen[23][80]);