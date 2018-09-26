#include "Headers/GUI/gui.h"
#include "Headers/GUI/gui_battery.h"
#include "Headers/GUI/gui_c_rnti.h"
#include "Headers/GUI/gui_logs.h"
#include "Headers/GUI/gui_progress_bar.h"

GUI_Battery gui_battery;
GUI_ProgressBar gui_progress_bar;
GUI_C_RNTI gui_c_rnti;
GUI_Logs gui_logs;

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
	initialize_gui_battery();
	initialize_gui_progress_bar();
	initialize_gui_c_rtni();
	initialize_gui_logs();

	while (true)
	{
		clear();
		create_screen(screen);

		gui_battery.draw_on_screen(screen);
		gui_c_rnti.draw_on_screen(screen);
		if (gui_progress_bar.is_enabled)
			gui_progress_bar.draw_on_screen(screen);
		if (gui_logs.is_enabled)
			gui_logs.draw_on_screen(screen);
		draw_screen(screen);
		usleep(100000);
	}
}