#include "thermal_model.h"

void update_thermal_model(VirtualBatteryPack_t* pack, int cell_index, float dt_ms){
    if (!pack || dt_ms <= 0.0f) return;
    const float dt_s = dt_ms / 1000.0f;

    const float Ti   = pack->temperature_c[cell_index];
    const float I    = pack->pack_current_a;
    const float Rint = pack->internal_resistance[cell_index];

    const float G_env = 1.0f / R_TH_ENV_C_PER_W;
    const float G_adj = 1.0f / R_TH_ADJ_C_PER_W;

    float P_self = I * I * Rint;

    float Qdot_neighbors = 0.0f;
    if (cell_index - 1 >= 0) {
        float Tn = pack->temperature_c[cell_index - 1];
        Qdot_neighbors += G_adj * (Tn - Ti);
    }
    if (cell_index + 1 < NUM_CELLS) {
        float Tn = pack->temperature_c[cell_index + 1];
        Qdot_neighbors += G_adj * (Tn - Ti);
    }

    float Qdot_ambient = G_env * (pack->ambient_temp_c - Ti);
    float Qdot_total = P_self + Qdot_neighbors + Qdot_ambient;

    float dT = (Qdot_total * dt_s) / CELL_HEAT_CAPACITY_J_PER_C;
    float Tnew = Ti + dT;
    if (Tnew < T_MIN_C) Tnew = T_MIN_C;
    if (Tnew > T_MAX_C) Tnew = T_MAX_C;

    pack->temperature_c[cell_index] = Tnew;
}