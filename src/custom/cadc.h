#ifndef CADC_H
#define CADC_H
#include "cstructs.h"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
// LOG_MODULE_REGISTER(CADC, LOG_LEVEL_DBG);

// Structures
static const struct adc_dt_spec adc_channel_temperature
    = ADC_DT_SPEC_GET (DT_PATH (zephyr_user));

// Functions
void initADC (void);
void readADC (void);

void convert_mv_to_temp_LM35 (const int32_t *val_mv, int32_t *val_temp);

#endif
