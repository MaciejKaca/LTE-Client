#include "Headers/GUI/gui.h"
#include "Headers/GUI/gui_battery.h"

GUI_Battery gui_battery;

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

	while (true)
	{
		clear();
		draw_screen(screen);
		gui_battery.draw_on_screen(screen);
		usleep(100000);
	}
}