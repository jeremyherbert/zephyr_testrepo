#include <zephyr.h>
#include <drivers/sensor.h>

#include "app_version.h"

#include <logging/log.h>

LOG_MODULE_REGISTER(main, CONFIG_APP_LOG_LEVEL);

void main(void)
{
	int ret;

	const struct device *dummy_accel;
	dummy_accel = DEVICE_DT_GET(DT_NODELABEL(dummyaccel0));
	
	if (!device_is_ready(dummy_accel)) {
		LOG_ERR("Sensor not ready");
		return;
	}

	printk("Zephyr Example Application %s\n", APP_VERSION_STR);

	while (1) {

		printk("hi\n");

		k_sleep(K_MSEC(1000));
	}
}

