#include "callbacks.h"
#include <zephyr/bluetooth/hci.h>
#include <zephyr/drivers/gpio.h>
LOG_MODULE_REGISTER(Callbacks, LOG_LEVEL_INF);
extern struct bt_conn* my_conn;
//
extern struct gpio_dt_spec led_bt_connected_status;
// extern struct bt_data ad[];
// extern struct bt_data sd[];
// extern struct bt_le_adv_param adv_param[];
extern void advertising_start();
struct bt_conn_cb bt_connection_callbacks = {
	.connected = on_connect,
	.disconnected = on_disconnect,
    .recycled = on_recycled,
};

//TODO handling
void on_connect(struct bt_conn *conn, uint8_t err){
	switch (err)
	{
	case BT_HCI_ERR_SUCCESS:
		LOG_INF("Connected Device");
		my_conn = bt_conn_ref(conn);
		gpio_pin_set_dt(&led_bt_connected_status, 1);
		break;
	case BT_HCI_ERR_UNKNOWN_CONN_ID:
		LOG_ERR("Connection failed: BT_HCI_ERR_UNKNOWN_CONN_ID");
		/* code */
		break;
	case BT_HCI_ERR_ADV_TIMEOUT:
		LOG_ERR("Connection failed: BT_HCI_ERR_ADV_TIMEOUT");
		break;
	default:
		break;
	}

};
//TODO handling
void on_disconnect(struct bt_conn *conn, uint8_t reason){
	LOG_INF("Disconnected Device : Reason %d",reason);
	switch (reason)
	{
	case BT_HCI_ERR_REMOTE_USER_TERM_CONN:
		LOG_INF("Remote user terminated connection");
		bt_conn_unref(my_conn);
		gpio_pin_set_dt(&led_bt_connected_status, 0);
		/* code */
		break;
	
	default:
		bt_conn_unref(my_conn);
		gpio_pin_set_dt(&led_bt_connected_status, 0);

		break;
	}
};

void on_recycled(void){
	LOG_INF("Recycling..");
	advertising_start();
}