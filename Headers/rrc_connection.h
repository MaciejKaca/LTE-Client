#pragma once
#include <stdint.h>

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
	char ue_identity[16]; // IMSI
	EstablishmentCause establishment_cause;
} RrcConnectionRequest;