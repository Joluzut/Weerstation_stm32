/*
 * Copyright (c) 2023 JSC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// #include <zephyr/kernel.h>
// #include <zephyr/device.h>
// #include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/drivers/eeprom.h>
#include "rtc.h"
#include "esp8266.h"

// #define EEPROM_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_i2c-target-eeprom)
#define NODE_EP1 DT_NODELABEL(eeprom1)
#define NODE_EP2 DT_NODELABEL(eeprom2)
#define rtc_device_node DT_NODELABEL(rtc) //RTC node
#define UART_DEVICE_NODE DT_NODELABEL(usart1) //Uart node


#define MICRO_TO_HUNDERDTH 10000

#define EEPROM_INTERNAL_BASE_ADDR 0xAF  // Read/write from internal addr 
#define EEPROM_BUFFER_LEN         10    // Read/write consecutive bytes



   	
static char rx_buf2[128];
// void rusa(const struct device *uart_dev, void *user_data)
// {
//     int ret;

//     ret = uart_poll_in(uart_dev, &uart_data);
//     if (ret == 0) {
//         // printk("Char: %c\n", uart_data);
//         // Put received data into the message queue
// 		// printk("Char: %c\n", uart_data);
//         ret = k_msgq_put(&uart_msgq, &uart_data, K_NO_WAIT);
//         if (ret != 0) {
//             printk("Failed to put data into message queue\n");
//         }
//     } else if (ret == -EAGAIN) {
//         // No data available, handle it accordingly
//     } else {
//         // Handle error, if any
//         printk("UART read error: %d\n", ret);
//     }
    
// }

void send_str(const struct device *dev, const char *str) {
    int msg_len = strlen(str);
 
    printk("Device %s sending: \"%s\"\n", dev->name, str);
    for (int i = 0; i < msg_len; i++) {
        uart_poll_out(dev, str[i]);
    }
 
}

void uartTest()
{
	struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
	static const struct device *const rtc_dev = DEVICE_DT_GET(rtc_device_node);

	if (!device_is_ready(uart_dev)) {
        printk("UART device not found!");
        return 0;
    }
 
    int ret = uart_irq_callback_user_data_set(uart_dev, readUsart, NULL);
 
    
    char recv_buf[1024];
    uart_irq_rx_enable(uart_dev);
    int index = 0;
	while(1)
	{
        char* resp;
        resp = sendESP("AT+RST\r\n", uart_dev, rst);
        printk("%s", resp);
        k_sleep(K_MSEC(10000));

        resp = sendESP("AT+CWJAP=\"iPhone van Joey\",\"123456789\"\r\n", uart_dev, at);
        printk("%s", resp);
        k_sleep(K_MSEC(12000));

        resp = sendESP("AT+CIPSNTPCFG=1,1,\"0.nl.pool.ntp.org\"\r\n", uart_dev, at);
        printk("%s", resp);
        k_sleep(K_MSEC(1000));

        resp = sendESP("AT+CIPSNTPTIME?\r\n", uart_dev, at);
        printk("%s", resp);
        k_sleep(K_MSEC(2000));
        parseTime(resp, rtc_dev);
		printk("Epoch Time: %lld\n", getEpochTime(rtc_dev));
		
	}

}

// void eeprom()
// {
// 		sensor_sample_fetch(sensor);
//     	sensor_channel_get(sensor, SENSOR_CHAN_AMBIENT_TEMP, &temp);
//     	sensor_channel_get(sensor, SENSOR_CHAN_PRESS, &press);
//     	sensor_channel_get(sensor, SENSOR_CHAN_HUMIDITY, &humidity);

//         data[0] = temp.val1;
// 		data[1] = temp.val2/10000;
//         data[2] = press.val1;
// 		data[3] = press.val2/10000;
//         data[4] = humidity.val1;
// 		data[5] = humidity.val2/10000;    
		
// 		printk("\n%d.%02d %d.%02d %d.%02d %d\n",
//         data[0], data[1], data[2], data[3], data[4], data[5], counter/6);
		
// 		for(int x = 0; x<6; x++)
// 		{
// 		// write data to eeprom device
// 		if(counter/6<720)
// 		{
// 			ret = eeprom_write(dev1, counter, &data[x], sizeof(data[x]));
// 		}
// 		else
// 		{
// 			ret = eeprom_write(dev2, counter-720, &data[x], sizeof(data[x]));
// 		}
// 		if (ret) {
// 			printk("Failed to write eeprom (%d)\n", ret);
// 		}
		
// 		// read data from eeprom device
// 		k_sleep(K_MSEC(100));
// 		if(counter/6<720)
// 		{
// 		ret = eeprom_read(dev1, counter, eeprom_data, sizeof(eeprom_data));
// 		}
// 		else
// 		{
// 		ret = eeprom_read(dev2, counter-720, eeprom_data, sizeof(eeprom_data));
// 		}
// 		if (ret) {
// 			printk("Failed to read eeprom (%d)\n", ret);
// 		}
// 		printk("(%d)",(uint16_t)(*eeprom_data));

// 		counter++;
// 		}
		
// 		if(counter/6 >= 1439)
// 		{
// 			counter = 0;
// 		}
// 		else
// 		{
// 			counter++;
// 		}
// 		k_sleep(K_MSEC(100));
// }

int main(void)
{
	// const struct device *const dev1 = DEVICE_DT_GET(NODE_EP1);
	// const struct device *const dev2 = DEVICE_DT_GET(NODE_EP2);
	// const struct device *sensor = DEVICE_DT_GET_ANY(bosch_bme280);
	// static const struct device *const rtc_dev = DEVICE_DT_GET(rtc_device_node);
	
	
	

	

    struct sensor_value temp, press, humidity;
	int8_t * data[5];

	int ret;
	int counter = 0;
	int8_t eeprom_data[sizeof(int8_t)];
	while (1) {
		// eeprom();
		uartTest();
	}
	return 0;
}
