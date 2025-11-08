#include "cgatt.h"
#include "cadc.h"
#include <zephyr/logging/log.h>

// LOG_MODULE_REGISTER("GATTService", LOG_LEVEL_INF);
extern struct adc_values_t adc_values;

BT_GATT_SERVICE_DEFINE (
    my_temperature_service, BT_GATT_PRIMARY_SERVICE (BT_UUID_ESS),
    BT_GATT_CHARACTERISTIC (BT_UUID_TEMPERATURE, BT_GATT_CHRC_READ,
                            BT_GATT_PERM_READ,
                            read_temperature_cb, NULL, &adc_values));

ssize_t
read_temperature_cb (struct bt_conn *conn, const struct bt_gatt_attr *attr,
                     void *buf, uint16_t len, uint16_t offset)
{
  struct adc_values_t *values = (struct adc_values_t *)attr->user_data;
  return bt_gatt_attr_read (conn, attr, buf, len, offset, &(values->temp_in_C),
                            sizeof (values->temp_in_C));
};
