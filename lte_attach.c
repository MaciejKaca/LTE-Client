#include "Headers/lte_attach.h"
#include "Headers/preambles.h"

extern int client_socket;

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
    return rap.sequence.ra_rnti ==
           output_preamble.sequence.ra_rnti;
}

void perform_random_access_procedure()
{
    RandomAccessPreamble rap = create_input_preamble();

    printf("Started: Random Access Procedure\n");
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
    printf("Uplink Resource Grant: %d\n", output_preamble.uplink_resource_grant);
    printf("Your C-RNTI: %d\n", output_preamble.temp_c_rnti);
    printf("---\n");
}

void lte_attach() { perform_random_access_procedure(); }