#pragma once

#include "common.h"

typedef struct Battery
{
    int charge;
    void (*battery_drain)(int, int);
    void (*battery_drain_start)(int, int);
    bool (*is_battery_charged)();
} Battery;

void create_battery();