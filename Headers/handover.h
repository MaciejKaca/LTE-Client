#pragma once

#include "common.h"

#define ADDRESS_LENGTH 4

typedef unsigned char byte;

typedef struct X2_Server_Info {
    unsigned short eNodeB_port;
    byte address[ADDRESS_LENGTH];
}X2_Server_Info;
