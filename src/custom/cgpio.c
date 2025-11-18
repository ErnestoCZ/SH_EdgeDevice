#include "cgpio.h"
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#define STATUS_LED_NODE DT_ALIAS(led_device_status)

LOG_MODULE_REGISTER(cgpio, LOG_LEVEL_ERR);

#ifdef DT_NODE_EXISTS(STATUS_LED_NODE)
static const struct gpio_dt_spec led_device_status = GPIO_DT_SPEC_GET(STATUS_LED_NODE, gpios);
#endif


int init_gpio(void){

    int ret = 0;
    if(gpio_is_ready_dt(&led_device_status)){
        ret = gpio_pin_configure_dt(&led_device_status,GPIO_OUTPUT | GPIO_ACTIVE_HIGH);
        // gpio_pin_set_dt(&led_device_status,GPIO_OUTPUT_LOW);
    }else{
        return 1;
    }

    return 0;

};