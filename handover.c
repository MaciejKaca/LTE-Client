#include "Headers/handover.h"
#include "Headers/GUI/gui_logs.h"

extern int client_socket;
extern UserEquipment user_equipment;
extern int C_RNTI;
X2_Server_Info backup_server_info;

void resolve_backup_server_info()
{
	read(client_socket, (void *)&backup_server_info,
		 sizeof(backup_server_info));
	char backup_server_ip[4];
	strncpy(backup_server_ip, backup_server_info.address, 4);

	char backup_server_address_string[50];
	sprintf(backup_server_address_string, "Backup server: %d.%d.%d.%d:%d",
			backup_server_info.address[0], backup_server_info.address[1],
			backup_server_info.address[2], backup_server_info.address[3],
			backup_server_info.eNodeB_port);

	if (backup_server_info.eNodeB_port == 0)
		sprintf(backup_server_address_string, "No backup server! Good luck.");
		
	add_log_entry(backup_server_address_string);
}

void resolve_handover_control()
{
	void *trash_buffer = malloc(1);
	read(client_socket, trash_buffer, sizeof(byte));
	free(trash_buffer);

	message_label measurment_report_label = {
		message_type : msg_handover_measurment_report,
		message_length : sizeof(user_equipment.signal_strength)
	};
	send_data(client_socket, &user_equipment.signal_strength,
			  measurment_report_label);
}

void reconnect_to_backup_server()
{
	// closing old connection
	close(client_socket);

	// check if backup server exists
	if (backup_server_info.eNodeB_port == 0)
	{
		exit(0);
	}

	// connecting to new server
	char backup_server_address_string[17];
	sprintf(backup_server_address_string, "%d.%d.%d.%d",
			backup_server_info.address[0], backup_server_info.address[1],
			backup_server_info.address[2], backup_server_info.address[3]);

	create_session(backup_server_address_string,
				   backup_server_info.eNodeB_port);
}

void resolve_handover_start()
{
	reconnect_to_backup_server();

	// connection authorization
	message_label handover_reconnection_label = {
		message_type : msg_handover_client_reconnection,
		message_length : sizeof(C_RNTI)
	};
	send_data(client_socket, (void *)&C_RNTI, handover_reconnection_label);

	int new_C_RNTI;
	message_label handover_reconnection_info_label;
	recive_data_blocking(client_socket, (void *)&new_C_RNTI,
						 &handover_reconnection_info_label);

	C_RNTI = new_C_RNTI;

	set_socket_non_blocking(client_socket);
	user_equipment.signal_strength = 100;
}

void handle_connection_lost()
{
	add_log_entry("Connection lost. Reconnecting.");
	reconnect_to_backup_server();
	lte_attach();
	set_socket_non_blocking(client_socket);
	add_log_entry("Reconnected succesfully");
}