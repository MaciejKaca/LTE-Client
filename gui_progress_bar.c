#include "Headers/GUI/gui_progress_bar.h"

extern GUI_ProgressBar gui_progress_bar;
extern Download_Info download_info;
extern int current_packet_number;

void draw_progress_bar_on_screen(char screen[23][80])
{
    int x = gui_progress_bar.x_position;
    char progress_bar_text[80];

    sprintf(progress_bar_text, "Received %d/%d packets.", 
        current_packet_number, download_info.number_of_packets);

    place_string_on_screen(screen[21], x, progress_bar_text, 40);
}

GUI_ProgressBar initialize_gui_progress_bar()
{
    gui_progress_bar.is_enabled = false;
	gui_progress_bar.x_position = 1;
	gui_progress_bar.y_position = 0;
	gui_progress_bar.draw_on_screen = draw_progress_bar_on_screen;
}