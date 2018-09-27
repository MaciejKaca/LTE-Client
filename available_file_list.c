#include "Headers/GUI/gui_available_file_list.h"

extern GUI_AvailableFileList gui_available_file_list;
extern char available_file_list[64];

GUI_AvailableFileList initialize_available_file_list()
{
    gui_available_file_list.is_enabled = false;
	gui_available_file_list.x_position = 1;
	gui_available_file_list.y_position = 0;
	gui_available_file_list.draw_on_screen = draw_available_file_list_on_screen;
}

void draw_available_file_list_on_screen(char screen[23][80])
{
    char file_text[] = "File list: ";
    int file_text_length = sizeof(file_text)/sizeof(char);
    place_string_on_screen(screen[18], 1, file_text, file_text_length);
    place_string_on_screen(screen[18], gui_available_file_list.x_position+file_text_length,
        available_file_list, 64);
}