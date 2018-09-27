#include "Headers/GUI/gui.h"
#include "Headers/GUI/gui_ue_info.h"
#include "Headers/GUI/gui_logs.h"
#include "Headers/GUI/gui_menu.h"
#include "Headers/GUI/gui_key_buffer.h"
#include "Headers/GUI/gui_progress_bar.h"
#include "Headers/GUI/gui_available_file_list.h"

GUI_UE_Info gui_ue_info;
GUI_ProgressBar gui_progress_bar;
GUI_KeyBuffer gui_key_buffer;
GUI_Logs gui_logs;
GUI_Menu gui_menu;
GUI_AvailableFileList gui_available_file_list;

void create_screen(char screen[23][80])
{
	for (int y = 0; y < 23; y++)
		for (int x = 0; x < 80; x++)
			screen[y][x] = ' ';

	for (int y = 1; y < 22; y++)
	{
		screen[y][0] = '|';
		screen[y][79] = '|';
	}

	for (int x = 1; x < 79; x++)
	{
		screen[0][x] = '=';
		screen[22][x] = '=';
	}
}

void draw_screen(char screen[23][80])
{
	for (int y = 0; y < 23; y++)
	{
		for (int x = 0; x < 80; x++)
			printf("%c", screen[y][x]);
		printf("\n");
	}
}

void draw_gui()
{
	char screen[23][80];
	create_screen(screen);
	initialize_gui_ue_info();
	initialize_gui_progress_bar();
	initialize_gui_logs();
	initialize_gui_menu();
	initialize_gui_key_buffer_bar();
	initialize_available_file_list();

	while (true)
	{
		clear();
		create_screen(screen);

		gui_ue_info.draw_on_screen(screen);


		if (gui_menu.is_enabled)
			gui_menu.draw_on_screen(screen);

		if (gui_progress_bar.is_enabled)
			gui_progress_bar.draw_on_screen(screen);
			
		gui_key_buffer.draw_on_screen(screen);	

		if (gui_logs.is_enabled)
			gui_logs.draw_on_screen(screen);

		if(gui_available_file_list.is_enabled)
			gui_available_file_list.draw_on_screen(screen);

		draw_screen(screen);
		usleep(100000);
	}
}