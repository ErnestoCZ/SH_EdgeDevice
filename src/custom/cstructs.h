#ifndef C_STRUCTS_H 
#define C_STRUCTS_H
#include <stdint.h>
//Structs -----------------------------
//ADC
struct adc_values_t{
    uint32_t temp_in_C;
    uint16_t temp_in_mv;
};
#endif //C_STRUCTS_H