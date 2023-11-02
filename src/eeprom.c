#include "eeprom.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/eeprom.h>

#define NODE_EP1 DT_NODELABEL(eeprom1)
#define NODE_EP2 DT_NODELABEL(eeprom2)
const struct device *const dev1 = DEVICE_DT_GET(NODE_EP1);
const struct device *const dev2 = DEVICE_DT_GET(NODE_EP2);

void writeEeprom(int counter, int8_t data)
{
	int ret;
	if (counter < 7200) {
		ret = eeprom_write(dev1, counter, &data, sizeof(data));
	} else {
		ret = eeprom_write(dev2, counter - 7200, &data, sizeof(data));
	}
	if (ret) {
		printk("Failed to write eeprom (%d)\n", ret);
	}
}

void writeBigEeprom(int counter, int32_t data)
{
	int ret;
	if (counter < 7200) {
		ret = eeprom_write(dev1, counter, &data, sizeof(data));
	} else {
		ret = eeprom_write(dev2, counter - 7200, &data, sizeof(data));
	}
	if (ret) {
		printk("Failed to write eeprom (%d)\n", ret);
	}
}

int8_t readEeprom(int counter)
{
	int ret;
	int8_t data;
	int8_t eeprom_data[sizeof(int8_t)];

	if (counter < 7200) {
		ret = eeprom_read(dev1, counter, eeprom_data, sizeof(eeprom_data));
	} else {
		ret = eeprom_read(dev2, counter - 7200, eeprom_data, sizeof(eeprom_data));
	}
	if (ret) {
		printk("Failed to read eeprom (%d)\n", ret);
	}
	
	data = (uint8_t)(*eeprom_data);
	return data;
}

int32_t readBigEeprom(int counter)
{
	int ret;
	int32_t data;
	int32_t eeprom_data[sizeof(int32_t)];

	if (counter < 7200) {
		ret = eeprom_read(dev1, counter, eeprom_data, sizeof(eeprom_data));
	} else {
		ret = eeprom_read(dev2, counter - 7200, eeprom_data, sizeof(eeprom_data));
	}
	if (ret) {
		printk("Failed to read eeprom (%d)\n", ret);
	}
	
	data = (uint32_t)(*eeprom_data);
	return data;
}