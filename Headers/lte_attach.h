#pragma once

#include "common.h"

RandomAccessPreamble create_input_preamble();

bool validate_preamble(RandomAccessPreamble rap, RRC_ConnectionRequest output_preamble);

void perform_random_access_procedure();

void lte_attach();