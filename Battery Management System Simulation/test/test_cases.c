#include <assert.h>
#include <math.h>
#include "battery_physics.h"
#include "ocv_model.h"
#include "thermal_model.h"

int float_is_finite(float x){ return isfinite(x); }

int main(void){
    // OCV returns finite value across range
    for (int s = 0; s <= 100; s += 10){
        float v = lookup_ocv_curve((float)s, 25.0f);
        assert(float_is_finite(v));
    }

    // Thermal should move temperature toward ambient when no current flows
    VirtualBatteryPack_t pack = {0};
    pack.ambient_temp_c = 25.0f;
    for (int i = 0; i < NUM_CELLS; i++){
        pack.temperature_c[i] = 40.0f;
        pack.internal_resistance[i] = 0.05f;
        pack.nominal_capacity_ah[i] = NOMINAL_CAPACITY_AH;
    }
    pack.pack_current_a = 0.0f;
    update_thermal_model(&pack, 0, 1000.0f);
    assert(pack.temperature_c[0] <= 40.0f);

    return 0;
}