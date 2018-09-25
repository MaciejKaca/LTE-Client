#include "Headers/GUI/gui.h"
#include "Headers/GUI/gui_battery.h"

char screen[23][80];

GUI_Battery gui_battery;

void create_screen()
{
	for (int y = 0; y < 23; y++)
		for (int x = 0; x < 80; x++)
			screen[y][x] = ' ';
}

void draw_screen()
{
	for (int y = 0; y < 23; y++)
		for (int x = 0; x < 80; x++)
			printf("%c", screen[y][x]);
	printf("\n");
}

void draw_gui()
{
	create_screen();
	initialize_gui_battery();

	while (true)
	{
		clear();
		draw_screen();
		gui_battery.draw_on_screen(screen);
		sleep(1);
	}
}