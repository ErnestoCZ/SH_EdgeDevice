#ifndef C_CALLBACKS_H 
#define C_CALLBACKS_H
#include <zephyr/bluetooth/conn.h>
#include <zephyr/logging/log.h>
#include <stdint.h>



//BLUETOOTH
struct bt_conn_cb bt_connection_callbacks;

void on_connect(struct bt_conn *conn, uint8_t err);
void on_disconnect(struct bt_conn *conn, uint8_t reason);
void on_recycled(void);
#endif //C_CALLBACKS_H