#pragma once

#include "common.h"

typedef struct Baterry
{
    int charge;
    void (*battery_drain)();
    void (*baterry_drain_start)();
    // TODO:
    //      - implement thread that regulary drains baterry
    //      - implement function that drains baterry by certain amount when called
    //      - eat flan
} Baterry;

void create_battery();