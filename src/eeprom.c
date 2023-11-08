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
//this function is for writing 1 byte to eeprom
	int ret;
	//because we use 2 eeprom chips the first half will be stored on one chip and the other on the other half
	if (counter < 7200) {
		ret = eeprom_write(dev1, counter, &data, sizeof(data));
	} else {
		//the -7200 is because the writing needs to start at 0 not 7200
		ret = eeprom_write(dev2, counter - 7200, &data, sizeof(data));
	}
	if (ret) {
		printk("Failed to write eeprom (%d)\n", ret);
	}
}

void writeBigEeprom(int counter, int32_t data)
{
//this function is for writing 4 bytes to eeprom
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
//this function is to read 1 byte from the eeprom chip
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
	k_sleep(K_USEC(5));
	return data;
}

int32_t readBigEeprom(int counter)
{
//this function is to read 4 bytes from the eeprom chip
	int ret;
	int32_t data;
	int32_t eeprom_data[sizeof(int8_t)];

	if (counter < 7200) {
		ret = eeprom_read(dev1, counter, eeprom_data, sizeof(eeprom_data));
	} else {
		ret = eeprom_read(dev2, counter - 7200, eeprom_data, sizeof(eeprom_data));
	}
	if (ret) {
		printk("Failed to read eeprom (%d)\n", ret);
	}
	
	data = (uint32_t)(*eeprom_data);
	k_sleep(K_USEC(10));
	return data;
}

storageData returnStorageData(int counter)
{
//this function return a struct with the data needed
	int dataCounter = counter;
	storageData data;
	data.time = readBigEeprom(dataCounter);
	dataCounter = dataCounter + 4;
	data.temp1 = readEeprom(dataCounter);
	dataCounter++;
	data.temp2 = readEeprom(dataCounter);
	dataCounter++;
	data.press1 = readEeprom(dataCounter);
	dataCounter++;
	data.press2 = readEeprom(dataCounter);
	dataCounter++;
	data.humid1 = readEeprom(dataCounter);
	dataCounter++;
	data.humid2 = readEeprom(dataCounter);
	printk("Time read from eeprom: %d\n", data.time);
	return data;
}