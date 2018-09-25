#pragma once

#include "../common.h"

#include "../download.h"
#include "gui_helper.h"

typedef struct GUI_ProgressBar
{
    bool is_enabled;
	int y_position;
    int x_position;
	void (*draw_on_screen)(char screen[23][80]);
} GUI_ProgressBar;

GUI_ProgressBar initialize_gui_progress_bar();

