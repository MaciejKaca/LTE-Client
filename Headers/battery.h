#pragma once

#include "common.h"

typedef struct Battery
{
    int charge;
    void (*battery_drain)();
    void (*battery_drain_start)();
    bool (*is_battery_critical)();
    bool (*is_battery_drained)();
} Battery;

void create_battery();