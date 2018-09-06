#pragma once
#include <stdint.h>

enum EstablishmentCause
{
	Emergency,
	HighPriorytyAccess,
	MobileTerminatingAccess,
	MobileOrientedSignalling,
	MobileOrientedData
};

typedef struct RrcConnectionRequest
{
	char c_rnti_type[8];
	int c_rnti;
	char ue_identity[16]; // IMSI
	EstablishmentCause establishment_cause;
} RrcConnectionRequest;