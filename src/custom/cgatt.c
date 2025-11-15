#include "cgatt.h"
#include "cadc.h"
#include <zephyr/logging/log.h>

// LOG_MODULE_REGISTER("GATTService", LOG_LEVEL_INF);
extern struct adc_values_t adc_values;
static const struct bt_gatt_cpf temp_cpf = {
  .format = 0x08,       // 0x0E = signed 16-bit integer (sint16)
  .exponent = 1,        // Value * 10^-2 (e.g., 2550 becomes 25.50)
  .unit = 0x272F,       // 0x272F = UUID for Celsius
  .name_space = 0x01,   // 0x01 (Bluetooth SIG)
  .description = 0x0000 // 0x0000 (No specific desc)
};

BT_GATT_SERVICE_DEFINE (
    my_temperature_service, BT_GATT_PRIMARY_SERVICE (BT_UUID_ESS),
    BT_GATT_CHARACTERISTIC (BT_UUID_TEMPERATURE,
                            BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY,
                            BT_GATT_PERM_READ, read_temperature_cb, NULL,
                            &adc_values),
    BT_GATT_CPF (&temp_cpf));
BT_GATT_SERVICE_DEFINE (
    my_led_service, BT_GATT_PRIMARY_SERVICE (BT_UUID_UDS),
    BT_GATT_CHARACTERISTIC (BT_UUID_HIDP,
                            BT_GATT_CHRC_READ | BT_GATT_CHRC_WRITE,
                            BT_GATT_PERM_READ | BT_GATT_PERM_WRITE, read_custom_data_cb, write_custom_data_cb,
                            NULL),
                            BT_GATT_CCC(led_state_changed_cb,BT_GATT_PERM_READ|BT_GATT_PERM_WRITE);
                          );

ssize_t
read_temperature_cb (struct bt_conn *conn, const struct bt_gatt_attr *attr,
                     void *buf, uint16_t len, uint16_t offset)
{
  struct adc_values_t *values = (struct adc_values_t *)attr->user_data;
  return bt_gatt_attr_read (conn, attr, buf, len, offset, &(values->temp_in_C),
                            sizeof (values->temp_in_C));
};
ssize_t read_custom_data_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset){
  return bt_gatt_attr_read(conn,attr,buf,len,offset,"1",sizeof("1"));
};
ssize_t write_custom_data_cb(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset){

};

void _init_cgattc (void) {};