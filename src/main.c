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
int main(void)
{
        LOG_INF("Device is starting...");

	initADC();


        // ret = bt_enable(NULL);

	while(1){
		readADC();
		//TODO add filter capabilities
		k_msleep(5000);
	};


        return 0;
}
