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
	

    struct sensor_value temp, press, humidity;
	int8_t * data[5];

	int ret;
	int counter = 0;
	int8_t eeprom_data[sizeof(int8_t)];
	while (1) {
		
		uartTest();
	}
	return 0;
}
