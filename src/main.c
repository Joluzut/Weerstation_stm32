/*
 * Copyright (c) 2023 JSC
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// #include <zephyr/kernel.h>
// #include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/drivers/eeprom.h>
#include "rtc.h"
#include "esp8266.h"
#include "eeprom.h"


// #define EEPROM_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_i2c-target-eeprom)
#define rtc_device_node DT_NODELABEL(rtc) //RTC node
#define UART_DEVICE_NODE DT_NODELABEL(usart1) //Uart node


#define MICRO_TO_HUNDERDTH 10000

#define EEPROM_INTERNAL_BASE_ADDR 0xAF  // Read/write from internal addr 
#define EEPROM_BUFFER_LEN         10    // Read/write consecutive bytes



   	
static char rx_buf2[128];

void startup(const struct device *uart_dev, const struct device *rtc_dev)
{
    while(1)
    {
        char* resp;
        resp = sendESP("AT+CWJAP=\"iPhone van Joey\",\"123456789\"\r\n", uart_dev, at);
        printk("%s", resp);
        k_sleep(K_MSEC(100));
        const char *lastFourCharacters = resp + strlen(resp) - strlen("FAIL\r\n");
        if(strcmp(lastFourCharacters, "FAIL\r\n") == 0)
        {
            continue;
        }
        resp = sendESP("AT+CIPSNTPCFG=1,1,\"0.nl.pool.ntp.org\"\r\n", uart_dev, at);
        printk("%s", resp);
        k_sleep(K_MSEC(1000));

        resp = sendESP("AT+CIPSNTPTIME?\r\n", uart_dev, at);
        printk("%s", resp);
        k_sleep(K_MSEC(1000));
        parseTime(resp, rtc_dev);
        k_sleep(K_MSEC(3000));
        break;
    }
}

void eeprom()
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

    startup(uart_dev, rtc_dev);


	while(1)
	{
        char* resp;
       
        measurementStruct meas = sendMeasurement(9,15, 100,92, 46,12, getEpochTime(rtc_dev), uart_dev);
		printk("Measurement sending: %s, %s, %s", meas.tcp, meas.cipsend, meas.request);
        resp = sendESP(meas.tcp, uart_dev, tcp);
        printk("%s", resp);
        k_sleep(K_MSEC(1500));
        

        resp = sendESP(meas.cipsend, uart_dev, tcp);
        printk("%s", resp);
        k_sleep(K_MSEC(1000));
        const char *lastFourCharacters = resp + strlen(resp) - strlen("ERROR\r\n");
        if(strcmp(lastFourCharacters, "ERROR\r\n") == 0)
        {
            startup(uart_dev, rtc_dev);
            continue;
        }
        resp = sendESP(meas.request, uart_dev, tcp);
        printk("%s", resp);
        k_sleep(K_MSEC(10000));

	}

}

int main(void)
{
	eeprom();
	uartTest();

	return 0;
}
