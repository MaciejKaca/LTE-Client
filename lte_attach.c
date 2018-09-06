#include "Headers/lte_attach.h"
#include "Headers/preambles.h"
#include "Headers/rrc_connection.h"

extern int client_socket;

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

	printf("Sending: Random Access Preamble...\n");
	printf("---\n");
	printf("Cyclic Prefix: %d\n", rap.cyclic_prefix);
	printf("%s: %d\n", rap.sequence.type, rap.sequence.ra_rnti);
	printf("---\n");

	int result = write(client_socket, (void *)&rap, sizeof(rap));

	if (result < 0)
		error("Couldn't write preamble to the server.");
	else
		printf("Preamble sent successfully!\n\n");

	printf("Reading: Random Access Response...\n");

	RandomAccessResponse output_preamble;
	result = read(client_socket, &output_preamble, sizeof(output_preamble));

	if (result < 0)
		error("Couldn't read output preamble from the server.");
	else
		printf("Preamble response red successfully!\n");

	result = validate_preamble(rap, output_preamble);
	if (result == false)
		error("Preambles do not match.\n");
	else
		printf("%s's match!\n\n", rap.sequence.type);

	printf("Random Acces Procedure succeded! \n");
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

	strncpy(rrc_c_request.ue_identity, "470010171566423", 16);
	rrc_c_request.establishment_cause = Emergency;

	return rrc_c_request;
}

RRC_Connection_Setup_Complete create_rrc_c_setup_complete()
{
	RRC_Connection_Setup_Complete rrc_c_setup_complete;

	char plmn[7];
	strncpy(plmn, "260", 7);
	strcat(plmn, "06");

	strncpy(rrc_c_setup_complete.plmn, plmn, 7);
	strcpy(rrc_c_setup_complete.dedicated_info_nas, "C1332BCCAD1231BAFF21");

	return rrc_c_setup_complete;
}

void rrc_connection_setup()
{
	printf("Started: RRC Connection Setup\n");

	RRC_Connection_Request rrc_c_request = create_rrc_c_request();

	int result =
		write(client_socket, (void *)&rrc_c_request, sizeof(rrc_c_request));
	if (result < 0)
		error("Couldn't write rrc_c_request to server.");
	else
		printf("RRC Connection request send.\n");

	RRC_connection_Setup rrc_c_setup;
	result = read(client_socket, (void *)&rrc_c_setup, sizeof(rrc_c_setup));
	if (result < 0)
		error("Couldn't read rrc_c_setup from server.");
	else
		printf("RRC Connection Setup received.\n");

	if (rrc_c_setup.c_rnti == C_RNTI)
		printf("RRC Connection Setup is correct.\n");

	printf("C-RNTI: %d\n", rrc_c_setup.c_rnti);
	printf("PHR Config: %d\n", rrc_c_setup.phr_config.periodic_PHR_Timer);
	printf("UPC Dedicated: %d\n", rrc_c_setup.UPC_Dedicatede.P0_UE_PUCCH);

	RRC_Connection_Setup_Complete rrc_c_setup_complete =
		create_rrc_c_setup_complete();

	result = write(client_socket, (void *)&rrc_c_setup_complete,
				   sizeof(rrc_c_setup_complete));
	if (result < 0)
		error("Couldn't write rrc_c_setup_complete to server.\n");
	else
		printf("RRC Connection Setup Complete send.\n");

	printf("RRC Connection succeded.\n");
}

void lte_attach()
{
	perform_random_access_procedure();
	rrc_connection_setup();
}