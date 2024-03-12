#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include <zephyr/device.h>

LOG_MODULE_REGISTER(simple_app);

int main(void)
{
	LOG_INF("Running PHSENSOR simple app on %s\n", CONFIG_BOARD);
	const struct device *dev = DEVICE_DT_GET_ANY(oemec);
	if (dev == NULL) {
		return 0;
	}
	LOG_INF("Device not NULL");
	return 0;
}
