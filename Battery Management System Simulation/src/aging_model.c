#include "aging_model.h"
void update_aging_model(VirtualBatteryPack_t* pack, int cell_index, float dt_ms){
    if (!pack) return;
    pack->calendar_age_hours[cell_index] += dt_ms / 3600000.0f;
}