#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/bluetooth/bluetooth.h>

LOG_MODULE_REGISTER(Smarthome_EdgeDevice, LOG_LEVEL_INF);
#include "cadc.h"
#include "cgatt.h"
#include "customCPP/filter.h"

void adc_thread_routine(void){
	k_msleep(2000);
	initADC();

	for(;;){
		readADC();
		k_msleep(5000);
	}
}

K_THREAD_DEFINE(adc_thread_id,512, adc_thread_routine,NULL ,NULL ,NULL , 7, K_USER, 0);

static const struct bt_data ad[] = {
	BT_DATA_BYTES(BT_DATA_FLAGS, BT_LE_AD_NO_BREDR),
	BT_DATA(BT_DATA_NAME_COMPLETE, CONFIG_BT_DEVICE_NAME,(sizeof(CONFIG_BT_DEVICE_NAME)-1)),
};
static const struct bt_le_adv_param adv_param[] = BT_LE_ADV_NCONN;

int main(void)
{
        LOG_INF("Device is starting...");

	// initADC();


	int ret = 0;

    ret = bt_enable(NULL);

	ret = bt_le_adv_start(adv_param,&ad,ARRAY_SIZE(ad),NULL,NULL);
	if(ret){
		LOG_ERR("Something gone wrong by start advertisements");
	}

	

	// while(1){
		// readADC();
		//TODO add filter capabilities
		// k_msleep(5000);
		// k_yield();
	// };


        return 0;
}
