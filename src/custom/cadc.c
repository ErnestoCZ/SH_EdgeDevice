#include "cadc.h"
#include <stdlib.h>
#include <zephyr/drivers/adc/adc_emul.h>
LOG_MODULE_REGISTER(CADC, LOG_LEVEL_INF);

static struct adc_sequence sequence;
static uint16_t adc_buffer;
struct value_range_t {
    int32_t from;
    int32_t to;
};

const int adc_emul_function(const struct device *dev, unsigned int chan,
                               void *data, uint32_t *result)
{
    ARG_UNUSED(dev);
    ARG_UNUSED(chan);

    // struct value_range_t *range = (struct value_range_t *)data;
    srand(k_cycle_get_32());
    *result = rand() % 300;
    return 0;
}

struct adc_values_t adc_values = {0, 0}; 

//TODO optimization of the error codes within function
/**
 * @brief 
 * 
 */
void initADC(void){
    int ret;
    
    if(adc_is_ready_dt(&adc_channel_temperature)){
        LOG_INF("ADC controller device %s is ready", adc_channel_temperature.dev->name);
    }else{
        LOG_ERR("ADC controller device %s is not ready", adc_channel_temperature.dev->name);
        return;
    };

    
    ret = adc_channel_setup_dt(&adc_channel_temperature);
    if(ret < 0){
        LOG_ERR("Failed to setup channel");
        return;
    }else{
        LOG_INF("Channel setup successful : ERRNO %d", ret);
    };

    //Configuration of the adc sequence struct
    sequence.channels = BIT(adc_channel_temperature.channel_id);
    sequence.buffer = &adc_buffer;
    sequence.buffer_size = sizeof(adc_buffer);
    sequence.resolution = adc_channel_temperature.resolution;
    

    if(adc_sequence_init_dt(&adc_channel_temperature, &sequence)){
        LOG_ERR("Failed to initialize sequence");
        return;
    }else{
        LOG_INF("Sequence initialized");
    };
    static struct value_range_t adc_mv_range = {
        .from = 0,
        .to = 1000,
    };
    adc_emul_value_func_set(adc_channel_temperature.dev, adc_channel_temperature.channel_id, adc_emul_function, &adc_mv_range);
    

}

/**
 * @brief This function is responsible to read and convert values if changed. 
 * Raw and converted values are stored in adc_values_t
 * 
 */
void readADC(void){
    int err = adc_read_dt(&adc_channel_temperature, &sequence);

    if(err < 0){
        LOG_ERR("Failed to read ADC");
    }else{
        int32_t val_mv;

        val_mv = (int32_t)adc_buffer;

        err = adc_raw_to_millivolts_dt(&adc_channel_temperature, &val_mv);
        if(err < 0){
            LOG_WRN("Failed to convert ADC value to mV");
        }
        else{
            int32_t val_temp;
            convert_mv_to_temp_LM35(&val_mv, &val_temp);
            // if(adc_values.temp_in_C != val_temp){
                adc_values.temp_in_mv = val_mv;
                adc_values.temp_in_C = val_temp;
                LOG_INF("ADC value: %d mV | Degrees Celsius: %d", val_mv, val_temp);
            // } 
        }
    }

}

/// @brief Functions converts received value in mv to temperature in degrees celsius based on documentation
/// @param val_mv value in millivolts
/// @param val_temp value in degree celsius
void convert_mv_to_temp_LM35(const int32_t *val_mv, int32_t *val_temp){
    *val_temp = (*val_mv / 10); // 
};