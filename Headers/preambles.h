#pragma once
#include <stdbool.h>

#include "sequence.h"

typedef struct RandomAccessPreamble
{
	char cyclic_prefix;
	Sequence sequence;
} RandomAccessPreamble;

typedef struct RandomAccessResponse
{
	Sequence sequence;
	int timing_advance_value;
	bool uplink_resource_grant;
	int temp_c_rnti; // Temporary ID assigned for this session to the UE
} RRC_ConnectionRequest;