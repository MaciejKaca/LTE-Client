#include "Headers/GUI/gui_logs.h"

extern GUI_Logs gui_logs;
extern UserEquipment user_equipment;
extern Queue *logs_queue;

void draw_logs_on_screen(char screen[23][80])
{
	int x = gui_logs.x_position;
	int y = gui_logs.y_position;

	reset_queue();
	for (int i = 0; i < logs_queue->size; i++)
	{
		place_string_on_screen(screen[y + i], x + 1, get_next_log_entry(), 50);
		place_string_on_screen(screen[y + i], x + 50, "|", 1);
	}
	place_string_on_screen(
		screen[y + logs_queue->size], x,
		"============================================================", 50);
}

GUI_Logs initialize_gui_logs()
{
	logs_queue = createQueue(5);
	gui_logs.is_enabled = true;
	gui_logs.x_position = 1;
	gui_logs.y_position = 1;
	gui_logs.draw_on_screen = draw_logs_on_screen;
}
