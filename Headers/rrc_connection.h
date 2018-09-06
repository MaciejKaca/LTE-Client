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

typedef struct RRC_Connection_Setup_Complete
{
	char plmn[7]; // Public Land Mobile Network ID ([MCC][MNC])
	char dedicated_info_nas[64]; // Octets carrying NAS Hex message
} RRC_Connection_Setup_Complete