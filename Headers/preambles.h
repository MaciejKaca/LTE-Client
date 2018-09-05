#pragma once
#include <stdbool.h>
#include <stdint.h>

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

typedef struct RandomAccessResponse
{
	Sequence sequence;
	int timing_advance_value;
	bool uplink_resource_grant;
	int temp_c_rnti; // Temporary ID assigned for this session to the UE
} RRC_ConnectionRequest;

// Serving Temporary Mobile Subscriber Identity
/*
	First attach to network - UE sends IMSI.
	If previously attached - UE sends S_TMSI.
*/
typedef struct S_TMSI 
{
	int8_t MMEC; // MME Code
	int32_t M_TMSI; // MME Mobile Subscriber Identity
} S_TMSI;