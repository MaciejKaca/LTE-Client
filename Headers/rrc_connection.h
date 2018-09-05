#pragma once
#include <stdint.h>

// Serving Temporary Mobile Subscriber Identity
/*
        First attach to network - UE sends IMSI.
        If previously attached - UE sends S_TMSI.
*/
typedef struct S_TMSI
{
	int8_t MMEC;	// MME Code
	int32_t M_TMSI; // MME Mobile Subscriber Identity
} S_TMSI;

typedef struct UE_Identity
{
	S_TMSI s_tmsi;
} UE_Identity;

typedef struct RRC_UE_ID_Type
{
	int c_rnti;
} RRC_UE_ID_Type;

enum EstablishmentCause // TODO: Check if this is good
{
	Emergency,
	HighPriorytyAccess,
	MobileTerminatingAccess,
	MobileOrientedSignalling,
	MobileOrientedData
};

typedef struct RrcConnectionRequest
{
	RRC_UE_ID_Type ue_id_type;
	char ue_id_value[16]; // IMEI
	UE_Identity ue_identity;
	EstablishmentCause establishment_cause;
} RrcConnectionRequest;