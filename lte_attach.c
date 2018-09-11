#include "Headers/lte_attach.h"
#include "Headers/preambles.h"
#include "Headers/rrc_connection.h"
#include "Headers/user_equipment.h"
#include "Headers/connection.h"

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
  printf("Cyclic Prefix: %d\n", rap.cyclic_prefix);
  printf("%s: %d\n", rap.sequence.type, rap.sequence.ra_rnti);
  printf("---\n");

  send_data(client_socket, (void *)&rap, sizeof(rap), &rap_label);

  RandomAccessResponse output_preamble;

  receive_data(client_socket, (void *)&output_preamble, sizeof(RandomAccessResponse));

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

  send_data(client_socket, (void *)&rrc_c_request, sizeof(rrc_c_request), &rrc_c_request_label);

  RRC_connection_Setup rrc_c_setup;

  receive_data(client_socket, (void *)&rrc_c_setup, sizeof(RRC_connection_Setup));

  printf("C-RNTI: %d\n", rrc_c_setup.c_rnti);
  printf("PHR Config: %d\n", rrc_c_setup.phr_config.periodic_PHR_Timer);
  printf("UPC Dedicated: %d\n", rrc_c_setup.UPC_Dedicatede.P0_UE_PUCCH);

  RRC_Connection_Setup_Complete rrc_c_setup_complete =
      create_rrc_c_setup_complete();

  message_label rrc_c_setup_complete_label =
    {
      message_type : msg_rrc_connection_setup,
      message_length : sizeof(RRC_Connection_Setup_Complete)
    };

  send_data(client_socket, (void *)&rrc_c_setup_complete, sizeof(rrc_c_setup_complete), &rrc_c_request_label);

  printf("RRC Connection succeded.\n");
}

void listen_to_server()
{
  int result;
  message_label label;

  while (user_equipment.battery.is_battery_drained() == false)
  {
    printf("PING THREAD\n");
    if (user_equipment.battery.is_battery_critical() == true)
      printf("Battery is low!\n");

    read_data(client_socket, (void *)&label, sizeof(message_label));

    printf("Message type: %d\n", label.message_type);

    sleep(5);
  }

  printf("Listening stopped.\n");
}

void start_server_listening_thread()
{
  printf("Started: Listening\n");
  thpool_add_work(thread_pool, (void *)listen_to_server, NULL);
}

void lte_attach()
{
  perform_random_access_procedure();
  rrc_connection_setup();
  printf("\n");
}