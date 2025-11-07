#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/kernel.h>

// create Service
//  #define BT_UUID_TEMP_SERVICE BT_UUID_GATT_TEMP_STAT

ssize_t read_temperature(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);