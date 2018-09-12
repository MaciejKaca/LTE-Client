#include "Headers/lte_attach.h"
#include "Headers/preambles.h"
#include "Headers/rrc_connection.h"
#include "Headers/user_equipment.h"
#include "Headers/connection.h"
#include "Headers/drx_config.h"

#include <pthread.h>

extern int client_socket;
extern UserEquipment user_equipment;
extern threadpool thread_pool;

int C_RNTI;

RandomAccessPreamble create_input_preamble()
{
  RandomAccessPreamble rap;
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
  message_label rap_label =
      {
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

  receive_data_blocking(client_socket, (void *)&output_preamble, &output_preamble_label);

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

  strncpy(rrc_c_request.rnti_type, "C-RNTI", 8);
  rrc_c_request.c_rnti = C_RNTI;

  strncpy(rrc_c_request.ue_identity, user_equipment.msin, 16);
  rrc_c_request.establishment_cause = Emergency;

  return rrc_c_request;
}

RRC_Connection_Setup_Complete create_rrc_c_setup_complete()
{
  RRC_Connection_Setup_Complete rrc_c_setup_complete;

  strncpy(rrc_c_setup_complete.plmn, user_equipment.plmn, 7);
  strcpy(rrc_c_setup_complete.dedicated_info_nas, "C1332BCCAD1231BAFF21");

  return rrc_c_setup_complete;
}

void rrc_connection_setup()
{
  printf("Started: RRC Connection Setup\n");

  RRC_Connection_Request rrc_c_request = create_rrc_c_request();
  message_label rrc_c_request_label =
      {
        message_type : msg_rrc_connection_request,
        message_length : sizeof(RRC_Connection_Request)
      };

  send_data(client_socket, (void *)&rrc_c_request, rrc_c_request_label);

  RRC_connection_Setup rrc_c_setup;
  message_label rrc_c_setup_label;

  receive_data_blocking(client_socket, (void *)&rrc_c_setup, &rrc_c_setup_label);

  printf("C-RNTI: %d\n", rrc_c_setup.c_rnti);
  printf("PHR Config: %d\n", rrc_c_setup.phr_config.periodic_PHR_Timer);
  printf("UPC Dedicated: %d\n", rrc_c_setup.UPC_Dedicatede.P0_UE_PUCCH);

  RRC_Connection_Setup_Complete rrc_c_setup_complete =
      create_rrc_c_setup_complete();

  message_label rrc_c_setup_complete_label =
    {
      message_type : msg_rrc_connection_setup_complete,
      message_length : sizeof(RRC_Connection_Setup_Complete)
    };

  send_data(client_socket, (void *)&rrc_c_setup_complete, rrc_c_setup_complete_label);

  printf("RRC Connection succeded.\n");
}

DRX_Config create_drx_config()
{
  DRX_Config drx_config;

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

  message_label drx_config_label = 
  {
    message_type : msg_drx_config,
    message_length: sizeof(DRX_Config)
  };

  printf("Sending DRX config.\n");
  send_data(client_socket, (void *)&drx_config,drx_config_label);
  printf("Sent DRX Config.\n");
}

void resolve_ping(bool ping_already_sent)
{
  char ping_response[64];
  char ping_request[64];

  message_label ping_response_label = 
  {
    message_type: msg_ping_response,
    message_length: sizeof(ping_response)
  };

  read(client_socket,(void*)ping_request,sizeof(ping_request));
  printf("------------------------------------------\n");
  printf("RECEIVED MESSAGE\n");
  printf("Type: msg_ping_request\n");
  printf("------------------------------------------\n");
  if(!ping_already_sent) send_data(client_socket, (void *)&ping_response, ping_response_label);
}

void listen_to_server()
{
  message_label label;
  
  while (user_equipment.battery.is_battery_drained() == false)
  {
    if (user_equipment.battery.is_battery_critical() == true)
      printf("Battery is low!\n");

    bool ping_sent = false;
    while(true)
    {
      int response = read(client_socket, (void *)&label, sizeof(message_label));
      if(response < 0)
        break;

      usleep(50000);
      if (response == sizeof(message_label))
		  {
        switch(label.message_type)
        {
          case msg_ping_request:
            resolve_ping(ping_sent);
            ping_sent = true;
            break;
			    default:
				    printf("Unknown message type.\n");
				    continue;
        }
      }
    }
    
    user_equipment.is_sleeping = true;
    printf("---Device goes to sleep.---\n");
    sleep(4);
    printf("\n---Device wakes up!---\n");
    usleep(100000);
    user_equipment.is_sleeping = false;
    sleep(1);
  }

  printf("Listening stopped.\n");
}

void start_server_listening_thread()
{
  printf("---\n");
  printf("Started: Listening\n");
  thpool_add_work(thread_pool, (void *)listen_to_server, NULL);
}

void lte_attach()
{
  perform_random_access_procedure();
  rrc_connection_setup();
  drx_config_setup();
  printf("\n");
}