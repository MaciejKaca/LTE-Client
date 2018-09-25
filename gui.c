#include "Headers/GUI/gui.h"
#include "Headers/GUI/gui_battery.h"

GUI_Battery gui_battery;

void create_screen(char screen[23][80])
{
	for (int y = 0; y < 23; y++)
		for (int x = 0; x < 80; x++)
		{
			screen[y][x] = ' ';
			if (x == 0 || x == 79)
				screen[y][x] = '|';
			if (y == 0 || y == 22)
				screen[y][x] = '-';
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
		sleep(1);
	}
}