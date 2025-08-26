#include "battery_physics.h"
#include "thermal_model.h"
#include <stdio.h>
#include <string.h>

int main(void) {
    VirtualBatteryPack_t pack;
    memset(&pack, 0, sizeof(pack));

    // ---- Initial conditions ----
    pack.pack_current_a = 2.0f;        // discharge (A); set negative for charge
    pack.ambient_temp_c = 25.0f;
    for (int i = 0; i < NUM_CELLS; i++) {
        pack.soc_percent[i]         = 50.0f;
        pack.temperature_c[i]       = 25.0f;
        pack.internal_resistance[i] = 0.05f;        // Ω
        pack.nominal_capacity_ah[i] = NOMINAL_CAPACITY_AH;
    }

    // ---- CSV logging to stdout ----
    // Columns: t_s, pack_current_a, v0..vN, t0..tN, soc0..socN
    printf("t_s,pack_current_a");
    for (int i = 0; i < NUM_CELLS; i++) printf(",v%d_V", i);
    for (int i = 0; i < NUM_CELLS; i++) printf(",temp%d_C", i);
    for (int i = 0; i < NUM_CELLS; i++) printf(",soc%d_pct", i);
    printf("\n");

    const float dt_ms = 100.0f; // 100 ms step
    for (int step = 0; step <= 600; step++) { // 60 s
        battery_physics_update(&pack, dt_ms);

        float t_s = step * (dt_ms / 1000.0f);
        printf("%.2f,%.3f", t_s, pack.pack_current_a);
        for (int i = 0; i < NUM_CELLS; i++) printf(",%.3f", pack.voltage_v[i]);
        for (int i = 0; i < NUM_CELLS; i++) printf(",%.3f", pack.temperature_c[i]);
        for (int i = 0; i < NUM_CELLS; i++) printf(",%.3f", pack.soc_percent[i]);
        printf("\n");
    }

    return 0;
}