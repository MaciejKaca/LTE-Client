#include "Headers/GUI/gui_progress_bar.h"

extern GUI_ProgressBar gui_progress_bar;
extern Download_Info download_info;
extern int current_packet_number;

void draw_progress_bar_on_screen(char screen[23][80])
{
 
    int x = gui_progress_bar.x_position;
    char progress_bar_status_text[80];
    sprintf(progress_bar_status_text, "Filename: %s | Received %d/%d packets.", 
        download_info.filename, current_packet_number, download_info.number_of_packets);

    place_string_on_screen(screen[20], x, progress_bar_status_text, 78);

    char progress_bar_text[78];
    memset(progress_bar_text, ' ', sizeof(progress_bar_text));
    create_progress_bar_text(progress_bar_text, sizeof(progress_bar_text));

    place_string_on_screen(screen[21], x, progress_bar_text, 78);

    if(current_packet_number == download_info.number_of_packets - 1)
        gui_progress_bar.is_enabled = false;
}

GUI_ProgressBar initialize_gui_progress_bar()
{
    gui_progress_bar.is_enabled = false;
	gui_progress_bar.x_position = 1;
	gui_progress_bar.y_position = 0;
	gui_progress_bar.draw_on_screen = draw_progress_bar_on_screen;
}

void create_progress_bar_text(char* str, int size)
{
    str[0] = '[';
    str[size - 1] = ']';

    int number_of_packets = download_info.number_of_packets;
    int number_of_signs = floor((current_packet_number / (float)number_of_packets) * 78) ;

    if(number_of_signs >= 1)
    {
        for(int i = 1; i < number_of_signs - 2; i++)
        {
            str[i] = '=';
            str[i+1] = '>';
        }
    }
}