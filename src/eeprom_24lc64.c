/*
 * Copyright (c) 2023 JSC
 *
 * SPDX-License-Identifier: Apache-2.0
 */


#include <zephyr/devicetree.h>
#include <zephyr/init.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/drivers/i2c.h>
#include <zephyr/sys/printk.h>
#include <zephyr/logging/log.h>
#include "eeprom_24lc64.h"

#define DT_DRV_COMPAT microchip_24lc64
#define EEPROM_24LC64_SIZE 8*1024  // 64kbits, 8kB
#define DT_EEPROM_SIZE_LABEL size

LOG_MODULE_REGISTER(eeprom_24lc64, CONFIG_LOG_DEFAULT_LEVEL);


struct eeprom_24lc64_config {
	struct i2c_dt_spec i2c;
	uint16_t size;
};

static size_t eeprom_24lc64_size(const struct device *dev)
{
	int size = ((struct eeprom_24lc64_config*)dev->config)->size;
	return size;

}

static bool check_eeprom_bounds(const struct device *dev, off_t offset,
			       size_t len)
{
	if ((offset + len) > eeprom_24lc64_size(dev) ) {
		return false;
	}

	return true;
}


static int eeprom_24lc64_write(const struct device *dev, off_t offset,
			       const void *data, size_t len)
{
	const struct eeprom_24lc64_config *config = dev->config;

	if (!check_eeprom_bounds(dev, offset, len)) {
		return -EINVAL;
	}

	struct i2c_msg msg[2];
	uint16_t address = ((offset & 0xFF) << 8) | ((offset >> 8) & 0xFF);

	msg[0].buf = (uint8_t *)&address;
	msg[0].len = sizeof(address);
	msg[0].flags = I2C_MSG_WRITE;

	msg[1].buf = (uint8_t *)data;
	msg[1].len = len;
	// possible flags: I2C_MSG_RESTART | I2C_MSG_WRITE | I2C_MSG_STOP
	msg[1].flags = I2C_MSG_WRITE | I2C_MSG_STOP;

	return i2c_transfer_dt(&config->i2c, msg, 2);
}



static int eeprom_24lc64_read(const struct device *dev, off_t offset, void *data,
			      size_t len)
{
	const struct eeprom_24lc64_config *config = dev->config;
	uint16_t address = ((offset & 0xFF) << 8) | ((offset >> 8) & 0xFF);
	
	if (!check_eeprom_bounds(dev, offset, len)) {
		return -EINVAL;
	}
	return i2c_write_read_dt(&config->i2c, &address, sizeof(address), data, len);
}

static int eeprom_24lc64_init(const struct device *dev)
{
	const struct eeprom_24lc64_config *config = dev->config;

	if (!device_is_ready(config->i2c.bus)) {
		// return -ENODEV;
	}

	return 0;
}

static const struct eeprom_driver_api eeprom_24lc64_api = {
	.read = eeprom_24lc64_read,
	.write = eeprom_24lc64_write,
	.size = eeprom_24lc64_size,
};

#define DEFINE_24LC64(inst)						       \
	static const struct eeprom_24lc64_config eeprom_24lc64_config##inst= { \
		.i2c =  I2C_DT_SPEC_INST_GET(inst),		       \
		.size = DT_PROP(DT_INST(inst, DT_DRV_COMPAT), size), \
	};								       \
	DEVICE_DT_INST_DEFINE(inst, eeprom_24lc64_init, NULL,	       \
			      NULL, &eeprom_24lc64_config##inst, POST_KERNEL,   \
			      51, &eeprom_24lc64_api);

DT_INST_FOREACH_STATUS_OKAY(DEFINE_24LC64);

