#include "Headers/lte_attach.h"
#include "Headers/preambles.h"
#include "Headers/rrc_connection.h"

extern int client_socket;

int C_RNTI;

RandomAccessPreamble create_input_preamble() {
  RandomAccessPreamble rap;
  rap.cyclic_prefix = ' ';

  int frequency = rand() % 64;
  int create_time = time(NULL);

  strncpy(rap.sequence.type, "RA-RNTI", 8);
  rap.sequence.ra_rnti = 1 + create_time + 10 * frequency;

  return rap;
}

bool validate_preamble(RandomAccessPreamble rap,
                       RandomAccessResponse output_preamble) {
  return rap.sequence.ra_rnti == output_preamble.sequence.ra_rnti;
}

void perform_random_access_procedure() {
  RandomAccessPreamble rap = create_input_preamble();
  int result = write(client_socket, (void *)&rap, sizeof(rap));
  if (result < 0)
    error("Couldn't write preamble to server.");

  RandomAccessResponse output_preamble;
  read(client_socket, &output_preamble, sizeof(output_preamble));

  result = validate_preamble(rap, output_preamble);
  if (result == false)
    error("Preambles do not match.");

  C_RNTI = output_preamble.temp_c_rnti;
  printf("Attach succeded. Your temp ID: %d", C_RNTI);
}

RRC_Connection_Request create_rrc_c_request() {
  RRC_Connection_Request rrc_c_request;

  strncpy(rrc_c_request.rnti_type, "C-RNTI", 8);
  rrc_c_request.c_rnti = C_RNTI;

  strncpy(rrc_c_request.ue_identity, "470010171566423", 16);
  rrc_c_request.establishment_cause = Emergency;

  return rrc_c_request;
}

RRC_Connection_Setup_Complete create_rrc_c_setup_complete() {
  RRC_Connection_Setup_Complete rrc_c_setup_complete;

  char plmn[7];
  strncpy(plmn, "260", 7);
  strcat(plmn, "06");

  strncpy(rrc_c_setup_complete.plmn, plmn, 7);
  strcpy(rrc_c_setup_complete.dedicated_info_nas, "C1332BCCAD1231BAFF21");

  return rrc_c_setup_complete;
}

void rrc_connection_setup() {
  RRC_Connection_Request rrc_c_request = create_rrc_c_request();

  int result =
      write(client_socket, (void *)&rrc_c_request, sizeof(rrc_c_request));
  if (result < 0)
    error("Couldn't write rrc_c_request to server.");

  RRC_connection_Setup rrc_c_setup;
  read(client_socket, (void *)&rrc_c_setup, sizeof(rrc_c_setup));

  if (rrc_c_setup.c_rnti == C_RNTI)
    printf("Received correct rrc_c_setup");

  RRC_Connection_Setup_Complete rrc_c_setup_complete =
      create_rrc_c_setup_complete();

  result = write(client_socket, (void *)&rrc_c_setup_complete,
                 sizeof(rrc_c_setup_complete));
  if (result < 0)
    error("Couldn't write rrc_c_setup_complete to server.");
}

void lte_attach() {
  perform_random_access_procedure();
  rrc_connection_setup();
}