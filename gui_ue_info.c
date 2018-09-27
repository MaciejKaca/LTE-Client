#include "Headers/GUI/gui_ue_info.h"
#include "Headers/GUI/gui_helper.h"

extern GUI_UE_Info gui_ue_info;
extern UserEquipment user_equipment;
extern int C_RNTI;

void draw_ue_info_on_screen(char screen[23][80])
{
	int x = gui_ue_info.x_position;
	int y = gui_ue_info.y_position;

	char battery_text[80];
	sprintf(battery_text, "Battery: %d%%", user_equipment.battery.charge);
	place_string_on_screen(screen[y], x, battery_text, 13);

	char signal_strength[80];
	sprintf(signal_strength, "Signal: %d%%", user_equipment.signal_strength);
	place_string_on_screen(screen[++y], x, signal_strength, 13);

	char c_rnti_text[80];
	sprintf(c_rnti_text, "C-RNTI: %d", C_RNTI);
	place_string_on_screen(screen[++y], x, c_rnti_text, 13);

	char enodeb_ip[30] = "IP: ";
	strcat(enodeb_ip, user_equipment.eNodeB.ip);
    place_string_on_screen(screen[++y], x, enodeb_ip, 20);

    char enodeb_port[30] = "Port: ";
    sprintf(enodeb_port + strlen(enodeb_port), "%d", user_equipment.eNodeB.port);
    place_string_on_screen(screen[++y], x, enodeb_port, 12);

}

GUI_UE_Info initialize_gui_ue_info()
{
	gui_ue_info.is_enabled = true;
	gui_ue_info.x_position = 59;
	gui_ue_info.y_position = 1;
	gui_ue_info.draw_on_screen = draw_ue_info_on_screen;
}