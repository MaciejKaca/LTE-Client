#include "Headers/GUI/gui_battery.h"

extern GUI_Battery gui_battery;
extern UserEquipment user_equipment;

void place_string_on_screen(char screen[80], int x, char text[80], int size)
{
	for (int i = 0; i < size; i++)
		screen[x + i] = text[i];
}

void draw_on_screen(char screen[23][80])
{
	int x = gui_battery.x_position;
	char battery_text[80];
	sprintf(battery_text, "Battery: %d%%", user_equipment.battery.charge);

	place_string_on_screen(screen[0], x, battery_text, 13);
}

GUI_Battery initialize_gui_battery()
{
	gui_battery.is_enabled = true;
	gui_battery.x_position = 67;
	gui_battery.y_position = 0;
	gui_battery.draw_on_screen = draw_on_screen;
}