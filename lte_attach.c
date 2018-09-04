#include "Headers/lte_attach.h"
#include "Headers/preambles.h"

extern int client_socket;

RandomAccessPreamble create_input_preamble()
{
    RandomAccessPreamble rap;
    rap.cyclic_prefix = ' ';
    strncpy(rap.sequence.ue_id_value, "355721065083448", 16);

    int frequency = rand() % 64;
    int create_time = time(NULL);
    rap.sequence.ue_id_type.ra_rnti = 1 + create_time + 10 * frequency;

    return rap;
}

bool validate_preamble(RandomAccessPreamble rap, RRC_ConnectionRequest output_preamble)
{
    return rap.sequence.ue_id_type.ra_rnti == output_preamble.sequence.ue_id_type.ra_rnti;
}

void perform_random_access_procedure()
{
    RandomAccessPreamble rap = create_input_preamble();
    int result = write(client_socket, (void *)&rap, sizeof(rap));
    if (result < 0)
        error("Couldn't write preamble to server.");

    RRC_ConnectionRequest output_preamble;
    read(client_socket, &output_preamble, sizeof(output_preamble));
    printf("%d", output_preamble.temp_c_rnti);

    result = validate_preamble(rap, output_preamble);
    if (result == false)
        error("Preambles do not match.");
}

void lte_attach()
{
    perform_random_access_procedure();
}