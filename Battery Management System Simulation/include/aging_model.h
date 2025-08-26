#ifndef AGING_MODEL_H
#define AGING_MODEL_H
#include "battery_physics.h"
void update_aging_model(VirtualBatteryPack_t* pack, int cell_index, float dt_ms);
#endif