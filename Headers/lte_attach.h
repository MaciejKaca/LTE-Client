#pragma once

#include "common.h"
#include "preambles.h"

RandomAccessPreamble create_input_preamble();

bool validate_preamble(RandomAccessPreamble rap, RandomAccessResponse output_preamble);

void perform_random_access_procedure();

void lte_attach();