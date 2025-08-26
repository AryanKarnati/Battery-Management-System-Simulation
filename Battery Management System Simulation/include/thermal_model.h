#pragma once
#include "battery_physics.h"

#ifndef CELL_HEAT_CAPACITY_J_PER_C
#define CELL_HEAT_CAPACITY_J_PER_C 450.0f
#endif

#ifndef R_TH_ENV_C_PER_W
#define R_TH_ENV_C_PER_W 8.0f
#endif

#ifndef R_TH_ADJ_C_PER_W
#define R_TH_ADJ_C_PER_W 1.2f
#endif

#ifndef T_MIN_C
#define T_MIN_C (-40.0f)
#endif

#ifndef T_MAX_C
#define T_MAX_C (120.0f)
#endif

void update_thermal_model(VirtualBatteryPack_t* pack, int cell_index, float dt_ms);