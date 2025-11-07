#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/conn.h>

LOG_MODULE_REGISTER(Smarthome_EdgeDevice, LOG_LEVEL_INF);
#include "cadc.h"
#include "cgatt.h"
#include "customCPP/filter.h"

//EXTERN
extern struct bt_conn_cb bt_connection_callbacks;

//PRIVATE FUNCTION PROTOTYPES
void adc_thread_handler(void);


//STATIC THREAD DEFINES
K_THREAD_DEFINE(adc_thread_id,512, adc_thread_handler,NULL ,NULL ,NULL , 7, K_USER, 0);

//BLE ADVERTISEMENTS AND RESPONSES
const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
	BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME,(sizeof(CONFIG_BT_DEVICE_NAME)-1)),
};
const struct bt_data sd[] = {
	BT_DATA_BYTES(BT_DATA_UUID16_ALL, BT_UUID_16_ENCODE(BT_UUID_TEMPERATURE_VAL)),
};
const struct bt_le_adv_param adv_param[] = BT_LE_ADV_PARAM((BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_SCANNABLE),
																	BT_GAP_ADV_SLOW_INT_MIN,
																	BT_GAP_ADV_SLOW_INT_MAX,
																	NULL);

int main(void)
{
    LOG_INF("Device is starting...");
	int ret = 0;

    ret = bt_enable(NULL);

	bt_conn_cb_register(&bt_connection_callbacks);

	ret = bt_le_adv_start(adv_param,&ad,ARRAY_SIZE(ad),&sd,ARRAY_SIZE(sd));
	if(ret){
		LOG_ERR("Something gone wrong by start advertisements");
	}

        return 0;
}


//FUNCTION DEFINITIONS
void adc_thread_handler(void){
	k_msleep(2000);
	initADC();

	for(;;){
		readADC();
		k_msleep(5000);
	}
}

