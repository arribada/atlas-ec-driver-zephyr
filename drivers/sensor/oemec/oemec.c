/*
 * Copyright (c) 2023 Arribada Initiative CIC
 *
 * SPDX-License-Identifier: MIT
 */
#define DT_DRV_COMPAT atlas_oemec

#include <zephyr/drivers/i2c.h>
#include <zephyr/logging/log.h>
#include <zephyr/sys/util.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/device.h>

LOG_MODULE_REGISTER(OEMEC, CONFIG_SENSOR_LOG_LEVEL);

#define OEMEC_DEVICE_TYPE         0x00
#define OEMEC_FW_VERSION          0x01
#define OEMEC_ADDR_UNLOCK         0x02
#define OEMEC_ADDR                0x03
#define OEMEC_INT_CONTROL         0x04
#define OEMEC_LED_CONTROL         0x05
#define OEMEC_ACT_HIBERNATE       0x06
#define OEMEC_NEW_READING         0x07
#define OEMEC_PROBE_MSB           0x08
#define OEMEC_PROBE_LSB           0x09
#define OEMEC_CALIB_MSB           0x0A
#define OEMEC_CALIB_HIGH_BYTE     0x0B
#define OEMEC_CALIB_LOW_BYTE      0x0C
#define OEMEC_CALIB_LSB           0x0D
#define OEMEC_CALIB_REQUEST       0x0E
#define OEMEC_CALIB_CONFIRM       0x0F
#define OEMEC_TEMP_COMP_MSB       0x10
#define OEMEC_TEMP_COMP_HIGH_BYTE 0x11
#define OEMEC_TEMP_COMP_LOW_BYTE  0x12U
#define OEMEC_TEMP_COMP_LSB       0x13
#define OEMEC_TEMP_CONF_MSB       0x14
#define OEMEC_TEMP_CONF_HIGH_BYTE 0x15
#define OEMEC_TEMP_CONF_LOW_BYTE  0x16
#define OEMEC_TEMP_CONF_LSB       0x17
#define OEMEC_SENSOR_MSB          0x18
#define OEMEC_SENSOR_HIGH_BYTE    0x19
#define OEMEC_SENSOR_LOW_BYTE     0x1A
#define OEMEC_SENSOR_LSB          0x1B
#define OEMEC_TDS_MSB             0x1C
#define OEMEC_TDS_HIGH_BYTE       0x1D
#define OEMEC_TDS_LOW_BYTE        0x1E
#define OEMEC_TDS_LSB             0x1F
#define OEMEC_SALINITY_MSB        0x20
#define OEMEC_SALINITY_HIGH_BYTE  0x21
#define OEMEC_SALINITY_LOW_BYTE   0x22
#define OEMEC_SALINITY_LSB        0x23

struct oemec_config {
	struct i2c_dt_spec bus;
	/* uint8_t resolution; */
	/* uint8_t mtreg; */
};

struct oemec_data {
	float sample;
};

static int oemec_sample_fetch(const struct device *dev, enum sensor_channel chan)
{
	LOG_INF("Fetching samples");
	return 0;
}
static int oemec_channel_get(const struct device *dev, enum sensor_channel chan,
			     struct sensor_value *val)
{
	LOG_INF("Fetching value for channel %d", chan);
	return 0;
}

static const struct sensor_driver_api oemec_driver_api = {
	.sample_fetch = oemec_sample_fetch,
	.channel_get = oemec_channel_get,
};

static int oemec_init(const struct device *dev)
{
	LOG_DBG("Inside oemec_init");
	return 0;
}

#define DEFINE_OEMEC(inst)                                                                         \
	static struct oemec_data oemec_data_##inst;                                                \
                                                                                                   \
	static const struct oemec_config oemec_config_##inst = {                                   \
		.bus = I2C_DT_SPEC_INST_GET(inst),                                                 \
	};                                                                                         \
	SENSOR_DEVICE_DT_INST_DEFINE(inst, oemec_init, NULL, &oemec_data_##inst,                   \
				     &oemec_config_##inst, POST_KERNEL,                            \
				     CONFIG_SENSOR_INIT_PRIORITY, &oemec_driver_api);

DT_INST_FOREACH_STATUS_OKAY(DEFINE_OEMEC)
