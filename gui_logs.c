#include "Headers/GUI/gui_logs.h"

extern GUI_Logs gui_logs;
extern UserEquipment user_equipment;
extern Queue *logs_queue;
extern Queue_Ping *ping_queue;

void draw_logs_on_screen(char screen[23][80])
{
	int x = gui_logs.x_position;
	int y = gui_logs.y_position;

	reset_queue();
	Ping_reset_queue();
	for (int i = 0; i < logs_queue->size; i++)
	{
		place_string_on_screen(screen[y + i], x + 1, get_next_log_entry(), 50);
		place_string_on_screen(screen[y + i], x + 50, "|", 1);
	}
	place_string_on_screen(
		screen[y + logs_queue->size], x,
		"============================================================", 50);
		place_string_on_screen(screen[y + logs_queue->size], x + 50, "|", 1);


	y = 10;
	place_string_on_screen(screen[y], x, "==========================", 26);
	place_string_on_screen(screen[y], x + 26, "|", 1);

	for (int i = 0; i < ping_queue->size; i++)
	{
		place_string_on_screen(screen[++y], x + 1, Ping_get_next_log_entry(),
							   50);
		place_string_on_screen(screen[y], x + 26, "|", 1);
	}
	place_string_on_screen(screen[++y], x, "==========================", 26);
	place_string_on_screen(screen[y], x + 26, "|", 1);
}

GUI_Logs initialize_gui_logs()
{
	logs_queue = createQueue(5);
	ping_queue = Ping_createQueue(3);
	gui_logs.is_enabled = true;
	gui_logs.x_position = 1;
	gui_logs.y_position = 1;
	gui_logs.draw_on_screen = draw_logs_on_screen;
}
