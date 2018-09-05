#pragma once 

typedef struct UE_ID_Type
{
	int ra_rnti;
} UE_ID_Type;

typedef struct Sequence
{
	char ue_id_value[16]; // IMEI
	UE_ID_Type ue_id_type;
} Sequence;