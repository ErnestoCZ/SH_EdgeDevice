#include "cgpio.h"
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(cgpio, LOG_LEVEL_DBG);

#define STATUS_LED_NODE DT_NODELABEL(led0)
#define STATUS_LED_ADV_NODE DT_NODELABEL(led1)
#define STATUS_LED_BT_CONNECTED_NODE DT_NODELABEL(led2)
#define BUTTON0 DT_NODELABEL(button0)
#define BUTTON1 DT_NODELABEL(button1)
#define BUTTON2 DT_NODELABEL(button2)
#define BUTTON3 DT_NODELABEL(button3)


// LEDs
#if DT_NODE_EXISTS(STATUS_LED_ADV_NODE) && DT_NODE_EXISTS(STATUS_LED_NODE)
const struct gpio_dt_spec led_adv_status =
    GPIO_DT_SPEC_GET(STATUS_LED_ADV_NODE, gpios);
const struct gpio_dt_spec led_device_status =
    GPIO_DT_SPEC_GET(STATUS_LED_NODE, gpios);
const struct gpio_dt_spec led_bt_connected_status =
    GPIO_DT_SPEC_GET(STATUS_LED_BT_CONNECTED_NODE, gpios);
#endif

// BUTTONS
#if DT_NODE_EXISTS(BUTTON0) && DT_NODE_EXISTS(BUTTON1) &&                      \
    DT_NODE_EXISTS(BUTTON2) && DT_NODE_EXISTS(BUTTON3)
const struct gpio_dt_spec button0 = GPIO_DT_SPEC_GET(BUTTON0, gpios);
const struct gpio_dt_spec button1 = GPIO_DT_SPEC_GET(BUTTON1, gpios);
const struct gpio_dt_spec button2 = GPIO_DT_SPEC_GET(BUTTON2, gpios);
const struct gpio_dt_spec button3 = GPIO_DT_SPEC_GET(BUTTON3, gpios);
#endif

static struct gpio_callback cb_button0;
static struct gpio_callback cb_button1;
static struct gpio_callback cb_button2;
static struct gpio_callback cb_button3;

void button0_callback(const struct device *port, struct gpio_callback *cb,
                      gpio_port_pins_t pins) {
  LOG_DBG("Button 0 pressed");
}
void button1_callback(const struct device *port, struct gpio_callback *cb,
                      gpio_port_pins_t pins) {
  LOG_DBG("Button 1 pressed");
                      }
void button2_callback(const struct device *port, struct gpio_callback *cb,
                      gpio_port_pins_t pins) {
  LOG_DBG("Button 2 pressed");
                      }
void button3_callback(const struct device *port, struct gpio_callback *cb,
                      gpio_port_pins_t pins) {
  LOG_DBG("Button 3 pressed");
}

int init_gpio(void) {

  int ret = 0;

  // LEDs
  if (gpio_is_ready_dt(&led_device_status)) {
    ret = gpio_pin_configure_dt(&led_device_status, GPIO_OUTPUT_INACTIVE);
  } else {
    return 1;
  }
  if (gpio_is_ready_dt(&led_adv_status)) {
    ret = gpio_pin_configure_dt(&led_adv_status, GPIO_OUTPUT_INACTIVE);
  } else {
    return 1;
  }
  if (gpio_is_ready_dt(&led_bt_connected_status)) {
    ret = gpio_pin_configure_dt(&led_bt_connected_status, GPIO_OUTPUT_INACTIVE);
  } else {
    return 1;
  }

  // Buttons
  if (gpio_is_ready_dt(&button0)) {
    ret = gpio_pin_configure_dt(&button0, GPIO_INPUT);
    ret = gpio_pin_interrupt_configure_dt(&button0, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&cb_button0, button0_callback, BIT(button0.pin));
    ret = gpio_add_callback_dt(&button0, &cb_button0);
  } else {
    return 1;
  }
  if (gpio_is_ready_dt(&button1)) {
    ret = gpio_pin_configure_dt(&button1, GPIO_INPUT);
    ret = gpio_pin_interrupt_configure_dt(&button1, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&cb_button1, button1_callback, BIT(button1.pin));
    ret = gpio_add_callback_dt(&button1, &cb_button1);
  } else {
    return 1;
  }
  if (gpio_is_ready_dt(&button2)) {
    ret = gpio_pin_configure_dt(&button2, GPIO_INPUT);
    ret = gpio_pin_interrupt_configure_dt(&button2, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&cb_button2, button2_callback, BIT(button2.pin));
    ret = gpio_add_callback_dt(&button2, &cb_button2);
  } else {
    return 1;
  }
  if (gpio_is_ready_dt(&button3)) {
    ret = gpio_pin_configure_dt(&button3, GPIO_INPUT);
    ret = gpio_pin_interrupt_configure_dt(&button3, GPIO_INT_EDGE_TO_ACTIVE);
    gpio_init_callback(&cb_button3, button3_callback, BIT(button3.pin));
    ret = gpio_add_callback_dt(&button3, &cb_button3);
  } else {
    return 1;
  }

  return 0;
};