#define DT_DRV_COMPAT zephyr_dummyaccel

#include <device.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(dummyaccel, CONFIG_SENSOR_LOG_LEVEL);

struct dummyaccel_data {
int sample_x;
	int sample_y;
	int sample_z;
	float gain;
};

struct dummyaccel_config {
	int dummy;
};

static int dummyaccel_sample_fetch(const struct device *dev,
					  enum sensor_channel chan)
{
	const struct dummyaccel_config *config = dev->config;
	struct dummyaccel_data *data = dev->data;

	switch (chan) {
		case SENSOR_CHAN_ACCEL_Z:
		case SENSOR_CHAN_ACCEL_Y:
		case SENSOR_CHAN_ACCEL_X:
		case SENSOR_CHAN_ACCEL_XYZ:
		case SENSOR_CHAN_ALL:
			break;
		default:
			return -ENOTSUP;
	}

	// insert dummy data
	data->gain = 1.0f;
	data->sample_x = 1;
	data->sample_y = 0;
	data->sample_z = 0;

	return 0;
}

static int dummyaccel_channel_get(const struct device *dev,
					 enum sensor_channel chan,
					 struct sensor_value *val)
{
	struct dummyaccel_data *data = dev->data;

	switch (chan) {
		case SENSOR_CHAN_ACCEL_X:
			sensor_value_from_double(val, data->sample_x * data->gain);
			break;
		case SENSOR_CHAN_ACCEL_Y:
			sensor_value_from_double(val, data->sample_y * data->gain);
			break;
		case SENSOR_CHAN_ACCEL_Z:
			sensor_value_from_double(val, data->sample_z * data->gain);
			break;
		default:
			return -ENOTSUP;
	}

	return 0;
}

static const struct sensor_driver_api dummyaccel_api = {
	.sample_fetch = &dummyaccel_sample_fetch,
	.channel_get = &dummyaccel_channel_get,
};

static int dummyaccel_init(const struct device *dev)
{
	const struct dummyaccel_config *config = dev->config;

	// nothing to configure

	return 0;
}

#define dummyaccel_INIT(i)						       \
	static struct dummyaccel_data dummyaccel_data_##i;	       \
										   \
	static const struct dummyaccel_config dummyaccel_config_##i = {  \
		.dummy = 1		       \
	};								       \
										   \
	DEVICE_DT_INST_DEFINE(i, dummyaccel_init, NULL,		       \
				  &dummyaccel_data_##i,			       \
				  &dummyaccel_config_##i, POST_KERNEL,	       \
				  CONFIG_SENSOR_INIT_PRIORITY, &dummyaccel_api);

DT_INST_FOREACH_STATUS_OKAY(dummyaccel_INIT)
