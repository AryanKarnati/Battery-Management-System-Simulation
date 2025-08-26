#include "battery_physics.h"
#include "ocv_model.h"
#include "thermal_model.h"
#include "aging_model.h"
#include "faults.h"

void battery_physics_update(VirtualBatteryPack_t* pack, float dt_ms) {
    for (int cell = 0; cell < NUM_CELLS; cell++) {
        float eff = calculate_charge_efficiency(pack->soc_percent[cell], pack->temperature_c[cell]);
        float dAh = (pack->pack_current_a * (dt_ms / 3600000.0f)); // A * h
        float dSoc_pct = (dAh / pack->nominal_capacity_ah[cell]) * 100.0f * eff;
        pack->soc_percent[cell] += dSoc_pct;

        // clamp SOC to 0..100 for stability
        if (pack->soc_percent[cell] < 0.0f) pack->soc_percent[cell] = 0.0f;
        if (pack->soc_percent[cell] > 100.0f) pack->soc_percent[cell] = 100.0f;

        float ocv = lookup_ocv_curve(pack->soc_percent[cell], pack->temperature_c[cell]);
        pack->voltage_v[cell] = ocv - pack->pack_current_a * pack->internal_resistance[cell];

        update_thermal_model(pack, cell, dt_ms);
        update_aging_model(pack, cell, dt_ms);
    }
    inject_simulated_faults(pack);
}