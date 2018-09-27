#pragma once

#include "../common.h"

#include "gui_helper.h"
#include "../detect_button.h"
typedef struct GUI_KeyBuffer
{
    bool is_enabled;
	int y_position;
    int x_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_KeyBuffer;

GUI_KeyBuffer initialize_gui_key_buffer_bar();

void draw_key_buffer_on_screen(char screen[23][80]);


