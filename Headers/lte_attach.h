#pragma once

#include "common.h"
#include "preambles.h"
#include "rrc_connection.h"
#include "drx_config.h"

RandomAccessPreamble create_input_preamble();

bool validate_preamble(RandomAccessPreamble rap,
					   RandomAccessResponse output_preamble);

void perform_random_access_procedure();

RRC_Connection_Request create_rrc_c_request();

RRC_Connection_Setup_Complete create_rrc_c_setup_complete();

void rrc_connection_setup();

DRX_Config create_drx_config();

void drx_config_setup();

void lte_attach();