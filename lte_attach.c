#include "Headers/lte_attach.h"
#include "Headers/connection.h"
#include "Headers/drx_config.h"
#include "Headers/handover.h"
#include "Headers/preambles.h"
#include "Headers/rrc_connection.h"
#include "Headers/user_equipment.h"

#include <pthread.h>

#define NAS_INFO "C1332BCCAD1231BAFF21"

extern int client_socket;
extern UserEquipment user_equipment;
extern threadpool thread_pool;

int C_RNTI;
X2_Server_Info backup_server_info;

RandomAccessPreamble create_input_preamble()
{
	RandomAccessPreamble rap;
	memset(&rap, 0, sizeof(RandomAccessPreamble));
	rap.cyclic_prefix = ' ';

	int frequency = rand() % 64;
	int create_time = time(NULL);

	strncpy(rap.sequence.type, "RA-RNTI", 8);
	rap.sequence.ra_rnti = 1 + create_time + 10 * frequency;

	return rap;
}

bool validate_preamble(RandomAccessPreamble rap,
					   RandomAccessResponse output_preamble)
{
	return rap.sequence.ra_rnti == output_preamble.sequence.ra_rnti;
}

void perform_random_access_procedure()
{
	printf("Started: Random Access Procedure\n");

	RandomAccessPreamble rap = create_input_preamble();
	message_label rap_label = {
		message_type : msg_random_access_preamble,
		message_length : sizeof(RandomAccessPreamble)
	};

	printf("Sending: Random Access Preamble...\n");
	printf("---\n");
	printf("Cyclic Prefix: '%c'\n", rap.cyclic_prefix);
	printf("%s: %d\n", rap.sequence.type, rap.sequence.ra_rnti);
	printf("---\n");

	send_data(client_socket, (void *)&rap, rap_label);

	RandomAccessResponse output_preamble;
	message_label output_preamble_label;
	memset(&output_preamble, 0, sizeof(RandomAccessResponse));
	memset(&output_preamble_label, 0, sizeof(message_label));

	recive_data_blocking(client_socket, (void *)&output_preamble,
						 &output_preamble_label);

	printf("Random Acces Procedure succeded.\n");
	printf("---\n");
	printf("Timing Advance Value: %d\n", output_preamble.timing_advance_value);
	printf("Uplink Resource Grant: %d\n",
		   output_preamble.uplink_resource_grant);
	printf("Your C-RNTI: %d\n", output_preamble.temp_c_rnti);
	printf("---\n");

	C_RNTI = output_preamble.temp_c_rnti;
}

RRC_Connection_Request create_rrc_c_request()
{
	RRC_Connection_Request rrc_c_request;
	memset(&rrc_c_request, 0, sizeof(RRC_Connection_Request));

	strncpy(rrc_c_request.rnti_type, "C-RNTI", 8);
	rrc_c_request.c_rnti = C_RNTI;

	strncpy(rrc_c_request.ue_identity, user_equipment.msin, 16);
	rrc_c_request.establishment_cause = Emergency;

	return rrc_c_request;
}

RRC_Connection_Setup_Complete create_rrc_c_setup_complete()
{
	RRC_Connection_Setup_Complete rrc_c_setup_complete;
	memset(&rrc_c_setup_complete, 0, sizeof(RRC_Connection_Setup_Complete));

	strncpy(rrc_c_setup_complete.plmn, user_equipment.plmn, 7);
	strcpy(rrc_c_setup_complete.dedicated_info_nas, NAS_INFO);

	return rrc_c_setup_complete;
}

void rrc_connection_setup()
{
	printf("Started: RRC Connection Setup\n");

	RRC_Connection_Request rrc_c_request = create_rrc_c_request();
	message_label rrc_c_request_label = {
		message_type : msg_rrc_connection_request,
		message_length : sizeof(RRC_Connection_Request)
	};

	send_data(client_socket, (void *)&rrc_c_request, rrc_c_request_label);

	RRC_connection_Setup rrc_c_setup;
	message_label rrc_c_setup_label;
	memset(&rrc_c_setup, 0, sizeof(RRC_connection_Setup));
	memset(&rrc_c_request_label, 0, sizeof(message_label));

	recive_data_blocking(client_socket, (void *)&rrc_c_setup,
						 &rrc_c_setup_label);

	printf("C-RNTI: %d\n", rrc_c_setup.c_rnti);
	printf("PHR Config: %d\n", rrc_c_setup.phr_config.periodic_PHR_Timer);
	printf("UPC Dedicated: %d\n", rrc_c_setup.UPC_Dedicatede.P0_UE_PUCCH);

	RRC_Connection_Setup_Complete rrc_c_setup_complete =
		create_rrc_c_setup_complete();

	message_label rrc_c_setup_complete_label = {
		message_type : msg_rrc_connection_setup_complete,
		message_length : sizeof(RRC_Connection_Setup_Complete)
	};

	send_data(client_socket, (void *)&rrc_c_setup_complete,
			  rrc_c_setup_complete_label);

	printf("RRC Connection succeded.\n");
}

void receive_backup_server_info()
{
	message_label new_enode_b_label;

	recive_data_blocking(client_socket, (void *)&backup_server_info,
						 (void *)&new_enode_b_label);
	char backup_server_ip[4];
	strncpy(backup_server_ip, backup_server_info.address, 4);

	printf("Backup server: %d.%d.%d.%d:%d\n", backup_server_ip[0],
		   backup_server_ip[1], backup_server_ip[2], backup_server_ip[3],
		   backup_server_info.eNodeB_port);
	printf("---\n");
}

DRX_Config create_drx_config()
{
	DRX_Config drx_config;
	memset(&drx_config, 0, sizeof(DRX_Config));

	drx_config.on_duration_timer = on_duration_timer_e_psf2;
	drx_config.drx_inactivity_timer = drx_inactivity_e_psf8;
	drx_config.drx_retransmission_timer = drx_retransmission_e_psf2;
	drx_config.long_drx_cycle_start_offset.label = long_drx_cycle_e_sf80;
	drx_config.long_drx_cycle_start_offset.value = 0;
	drx_config.short_drx.cycle = short_drx_e_sf40;
	drx_config.short_drx.DRX_Short_Cycle_Timer = 3;

	return drx_config;
}

void drx_config_setup()
{
	printf("---\n");
	DRX_Config drx_config = create_drx_config();

	message_label drx_config_label = {
		message_type : msg_drx_config,
		message_length : sizeof(DRX_Config)
	};

	printf("Sending DRX config.\n");
	send_data(client_socket, (void *)&drx_config, drx_config_label);
	printf("Sent DRX Config.\n");
}

void lte_attach()
{
	perform_random_access_procedure();
	rrc_connection_setup();
	drx_config_setup();
	receive_backup_server_info();
	printf("\n");
}