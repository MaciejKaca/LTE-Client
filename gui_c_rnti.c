#include "Headers/GUI/gui_c_rnti.h"
#include "Headers/GUI/gui_helper.h"

extern GUI_C_RNTI gui_c_rnti;
extern int C_RNTI;

void draw_c_rnti_on_screen(char screen[23][80])
{
	int x = gui_c_rnti.x_position;
	int y = gui_c_rnti.y_position;
	char c_rnti_text[80];
	sprintf(c_rnti_text, "C-RNTI: %d", C_RNTI);

	place_string_on_screen(screen[y], x, c_rnti_text, 13);
}

GUI_C_RNTI initialize_gui_c_rtni()
{
	gui_c_rnti.is_enabled = true;
	gui_c_rnti.x_position = 66;
	gui_c_rnti.y_position = 2;
	gui_c_rnti.draw_on_screen = draw_c_rnti_on_screen;
}