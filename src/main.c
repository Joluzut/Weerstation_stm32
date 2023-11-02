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
#include "eeprom.h"


// #define EEPROM_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_i2c-target-eeprom)
#define MICRO_TO_HUNDERDTH 10000

#define EEPROM_INTERNAL_BASE_ADDR 0xAF  // Read/write from internal addr 
#define EEPROM_BUFFER_LEN         10    // Read/write consecutive bytes

int main(void)
{
	const struct device *sensor = DEVICE_DT_GET_ANY(bosch_bme280);
    struct sensor_value temp, press, humidity;
	int8_t * data[6];
	int counterWrite = 0;
	int counterRead = 0;
	int8_t recieved;
	int32_t time = 1698849621;
	int32_t recievedtime;
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
		
		printk("\n%d %d.%02d %d.%02d %d.%02d %d\n",
        time, data[0], data[1], data[2], data[3], data[4], data[5], counterWrite/10);

		writeBigEeprom(counterWrite,time);
		counterWrite = counterWrite + 4;
		time++;
		k_sleep(K_MSEC(5));
		for(int x = 0; x<6; x++)
		{
		writeEeprom(counterWrite,data[x]);
		counterWrite++;
		k_sleep(K_MSEC(5));
		}

		recievedtime = readBigEeprom(counterRead);
		counterRead = counterRead + 4;
		printk("(%d)", recievedtime);
		k_sleep(K_MSEC(5));
		for(int x = 0; x<6; x++)
		{
		recieved = readEeprom(counterRead);
		printk("(%d)", recieved);
		counterRead++;
		k_sleep(K_MSEC(5));
		}

		if(counterWrite > 14400)
		{
			counterWrite = 0;
		}

		if(counterRead > 14400)
		{
			counterRead = 0;
		}
		k_sleep(K_MSEC(1));
	}
	return 0;
}
