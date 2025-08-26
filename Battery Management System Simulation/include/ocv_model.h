#ifndef OCV_MODEL_H
#define OCV_MODEL_H
float lookup_ocv_curve(float soc_percent, float temp_c);
float calculate_charge_efficiency(float soc_percent, float temp_c);
#endif