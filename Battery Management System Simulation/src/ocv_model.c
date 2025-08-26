#include "ocv_model.h"

#define NUM_TEMPS 3
#define NUM_SOC   11

static const float temp_table[NUM_TEMPS] = {0.0f, 25.0f, 50.0f};
static const float soc_table[NUM_SOC] = {0,10,20,30,40,50,60,70,80,90,100};

static const float ocv_table[NUM_TEMPS][NUM_SOC] = {
    //           0%   10%  20%  30%  40%  50%  60%  70%  80%  90%  100%
    /* 0°C  */ {3.00,3.30,3.45,3.55,3.65,3.70,3.75,3.85,3.95,4.05,4.15},
    /* 25°C */ {3.10,3.40,3.55,3.65,3.72,3.80,3.90,4.00,4.05,4.12,4.20},
    /* 50°C */ {3.15,3.45,3.58,3.68,3.75,3.85,3.95,4.03,4.10,4.17,4.22}
};

static float clamp(float x, float a, float b){
    return x < a ? a : (x > b ? b : x);
}
static float lerp(float a, float b, float t){ return a + (b - a) * t; }

float lookup_ocv_curve(float soc_percent, float temp_c){
    // clamp inputs
    float soc = clamp(soc_percent, 0.0f, 100.0f);
    float T   = clamp(temp_c, temp_c < temp_table[0] ? temp_table[0] : temp_c, temp_table[NUM_TEMPS-1]);

    // find temperature indices
    int t_idx = 0;
    while (t_idx + 1 < NUM_TEMPS - 0 && temp_table[t_idx + 1] <= T) t_idx++;
    if (t_idx >= NUM_TEMPS - 1) t_idx = NUM_TEMPS - 2;
    float t0 = temp_table[t_idx], t1 = temp_table[t_idx + 1];
    float temp_alpha = (T - t0) / (t1 - t0);

    // find soc indices
    int s_idx = 0;
    while (s_idx + 1 < NUM_SOC && soc_table[s_idx + 1] <= soc) s_idx++;
    if (s_idx >= NUM_SOC - 1) s_idx = NUM_SOC - 2;
    float s0 = soc_table[s_idx], s1 = soc_table[s_idx + 1];
    float soc_alpha = (soc - s0) / (s1 - s0);

    float v00 = ocv_table[t_idx][s_idx];
    float v01 = ocv_table[t_idx][s_idx + 1];
    float v10 = ocv_table[t_idx + 1][s_idx];
    float v11 = ocv_table[t_idx + 1][s_idx + 1];

    float ocv_low  = lerp(v00, v01, soc_alpha);
    float ocv_high = lerp(v10, v11, soc_alpha);
    return lerp(ocv_low, ocv_high, temp_alpha);
}

float calculate_charge_efficiency(float soc_percent, float temp_c){
    (void)soc_percent; (void)temp_c;
    return 0.98f; // placeholder
}