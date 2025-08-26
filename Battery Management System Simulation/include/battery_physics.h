#ifndef BATTERY_PHYSICS_H
#define BATTERY_PHYSICS_H

#define NUM_CELLS 4
#define NOMINAL_CAPACITY_AH 3.2f // example nominal capacity per cell

typedef struct {
    float soc_percent[NUM_CELLS];
    float temperature_c[NUM_CELLS];
    float voltage_v[NUM_CELLS];
    float internal_resistance[NUM_CELLS];
    float nominal_capacity_ah[NUM_CELLS];

    float pack_current_a;
    float pack_voltage_v;
    float pack_temperature_c;
    float pack_internal_resistance;

    float ambient_temp_c;

    float calendar_age_hours[NUM_CELLS];
    float cycle_throughput_ah[NUM_CELLS];

    int fault_flags[NUM_CELLS];
} VirtualBatteryPack_t;

void battery_physics_update(VirtualBatteryPack_t* pack, float dt_ms);

#endif