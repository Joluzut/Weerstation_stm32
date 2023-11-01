/*
 * Copyright (c) 2023 JSC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/eeprom.h>
#include "rtc.h"

// #define EEPROM_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_i2c-target-eeprom)
#define NODE_EP1 DT_NODELABEL(eeprom1)
#define NODE_EP2 DT_NODELABEL(eeprom2)
#define MICRO_TO_HUNDERDTH 10000

#define EEPROM_INTERNAL_BASE_ADDR 0xAF  // Read/write from internal addr 
#define EEPROM_BUFFER_LEN         10    // Read/write consecutive bytes

int main(void)
{
	const struct device *const dev1 = DEVICE_DT_GET(NODE_EP1);
	const struct device *const dev2 = DEVICE_DT_GET(NODE_EP2);
	const struct device *sensor = DEVICE_DT_GET_ANY(bosch_bme280);
	const struct device *rtc_dev = getRtc();
	
	struct tm rtc_time = {
        .tm_year = 2023-1900,
        .tm_mon = 10,
        .tm_mday = 1,
        .tm_hour = 12,
        .tm_min = 0,
        .tm_sec = 0
    };
	rtc_set_time(rtc_dev, &rtc_time);
	time_t timeSinceEpoch;

    struct sensor_value temp, press, humidity;
	int8_t * data[5];

	int ret;
	int counter = 0;
	int8_t eeprom_data[sizeof(int8_t)];
	while (1) {

		sensor_sample_fetch(sensor);
    	sensor_channel_get(sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    	sensor_channel_get(sensor, SENSOR_CHAN_PRESS, &press);
    	sensor_channel_get(sensor, SENSOR_CHAN_HUMIDITY, &humidity);

        data[0] = temp.val1;
		data[1] = temp.val2/10000;
        data[2] = press.val1;
		data[3] = press.val2/10000;
        data[4] = humidity.val1;
		data[5] = humidity.val2/10000;    
		
		printk("\n%d.%02d %d.%02d %d.%02d %d\n",
        data[0], data[1], data[2], data[3], data[4], data[5], counter/6);
		
		for(int x = 0; x<6; x++)
		{
		// write data to eeprom device
		if(counter/6<720)
		{
			ret = eeprom_write(dev1, counter, &data[x], sizeof(data[x]));
		}
		else
		{
			ret = eeprom_write(dev2, counter-720, &data[x], sizeof(data[x]));
		}
		if (ret) {
			printk("Failed to write eeprom (%d)\n", ret);
		}
		
		// read data from eeprom device
		k_sleep(K_MSEC(100));
		if(counter/6<720)
		{
		ret = eeprom_read(dev1, counter, eeprom_data, sizeof(eeprom_data));
		}
		else
		{
		ret = eeprom_read(dev2, counter-720, eeprom_data, sizeof(eeprom_data));
		}
		if (ret) {
			printk("Failed to read eeprom (%d)\n", ret);
		}
		printk("(%d)",(uint16_t)(*eeprom_data));

		counter++;
		}
		
		if(counter/6 >= 1439)
		{
			counter = 0;
		}
		else
		{
			counter++;
		}
		k_sleep(K_MSEC(100));
	}
	return 0;
}
