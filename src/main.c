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


// #define EEPROM_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_i2c-target-eeprom)
#define NODE_EP1 DT_NODELABEL(eeprom1)
#define MICRO_TO_HUNDERDTH 10000

#define EEPROM_INTERNAL_BASE_ADDR 0xAF  // Read/write from internal addr 
#define EEPROM_BUFFER_LEN         10    // Read/write consecutive bytes

int main(void)
{
	const struct device *const dev = DEVICE_DT_GET(NODE_EP1);
	const struct device *sensor = DEVICE_DT_GET_ANY(bosch_bme280);
    struct sensor_value temp, press, humidity;
	uint8_t * data[4][1439];
	int8_t * tempData[1439];

	int ret;
	uint16_t counter = 0;
	uint8_t eeprom_data[sizeof(uint16_t)];
	while (1) {
		printk( "Value: (%d)\n", counter);

		// write data to eeprom device
		ret = eeprom_write(dev, EEPROM_INTERNAL_BASE_ADDR, &counter, sizeof(counter));
		if (ret) {
			printk("Failed to write eeprom (%d)\n", ret);
		}

		// read data from eeprom device
		k_sleep(K_MSEC(100));
		ret = eeprom_read(dev, EEPROM_INTERNAL_BASE_ADDR, eeprom_data, sizeof(eeprom_data));
		if (ret) {
			printk("Failed to read eeprom (%d)\n", ret);
		}

		// check
		if (counter != (uint16_t)(*eeprom_data)){
			printk("Failed to read back eeprom (%d) (%d)\n",counter, (uint16_t)(*eeprom_data));
		} else {
			printk("Success reading back eeprom (%d) (%d)\n",counter, (uint16_t)(*eeprom_data));
		}
		
		sensor_sample_fetch(sensor);
    	sensor_channel_get(sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    	sensor_channel_get(sensor, SENSOR_CHAN_PRESS, &press);
    	sensor_channel_get(sensor, SENSOR_CHAN_HUMIDITY, &humidity);

        tempData[counter] = temp.val1;
        data[0][counter]  = press.val1;
        data[1][counter]  = humidity.val1;
        data[2][counter]  = temp.val2/10000;
    	data[3][counter]  = press.val2/10000;
        data[4][counter]  = humidity.val2/10000;

		printk("temperatuur: %d.%02d; luchtdruk: %d.%02d; luchtvochtigheid: %d.%02d; Teller: %d\n",
        tempData[counter], data[2][counter], data[0][counter], data[3][counter], data[1][counter], data[4][counter], counter);
		
		if(counter >= 1439)
		{
			counter = 0;
		}
		else
		{
			counter++;
		}
		k_sleep(K_MSEC(1000));
	}
	return 0;
}
