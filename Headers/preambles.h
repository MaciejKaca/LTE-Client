#pragma once
#include <stdbool.h>

typedef struct UE_ID_Type
{
	int ra_rnti;
} UE_ID_Type;

typedef struct Sequence
{
	char ue_id_value[16]; // IMEI
	UE_ID_Type ue_id_type;
} Sequence;

typedef struct RandomAccessPreamble
{
	char cyclic_prefix;
	Sequence sequence;
} RandomAccessPreamble;

typedef struct RRC_ConnectionRequest
{
	Sequence sequence;
	int timing_advance_value;
	bool uplink_resource_grant;
	int temp_c_rnti; // Temporary ID assigned for this session to the UE
} RRC_ConnectionRequest;
