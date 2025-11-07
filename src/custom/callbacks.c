#include "callbacks.h"

LOG_MODULE_REGISTER(Callbacks, LOG_LEVEL_INF);

struct bt_conn_cb bt_connection_callbacks = {
	.connected = on_connect,
	.disconnected = on_disconnect,
    .recycled = on_recycled,
};

//TODO handling
void on_connect(struct bt_conn *conn, uint8_t err){
	if(!err){
		LOG_INF("Connected by Device");
	}else{
		LOG_ERR("Connection error %s", err);
	}

};
//TODO handling
void on_disconnect(struct bt_conn *conn, uint8_t reason){
	LOG_INF("Disconnected Device");
};

void on_recycled(void){

}