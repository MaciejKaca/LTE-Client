#pragma once
#include <stdint.h>

#include "sequence.h"

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