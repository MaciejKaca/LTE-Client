#include "Headers/lte_attach.h"
#include "Headers/preambles.h"

extern int client_socket;

void perform_random_access_procedure()
{
	RandomAccessPreamble rap;
	rap.cyclic_prefix = ' ';
	strncpy(rap.sequence.ue_id_value,"355721065083448",16);
}

void lte_attach()
{
	perform_random_access_procedure();
}