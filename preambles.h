#pragma once
#include <stdbool.h>

struct UE_ID_Type
{
	int ra_rnti;
};

struct Sequence
{
	char[15] ue_id_value; // IMEI
	struct UE_ID_Type ue_id_type;
};

struct RandomAccessPreamble
{
	char cyclic_prefix;
	struct Sequence sequence;
};

struct RRC_ConnectionRequest
{
	struct Sequence sequence;
	int timing_advance_value;
	bool uplink_resource_grant;
	int temp_c_rnti; // Temporary ID assigned for this session to the UE
};