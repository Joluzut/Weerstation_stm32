#include <zephyr/devicetree.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/drivers/eeprom.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/__assert.h>
#include <zephyr/drivers/eeprom.h>
#include "rtc.h"
#include "esp8266.h"
#include "eeprom.h"

#define STACKSIZE_UPLOAD 1300
#define STACKSIZE_WIFI 350 //smaller does not work
#define STACKSIZE_SLEEP 300
#define STACKSIZE_EEPROM 470 // smaller does not work


#define rtc_device_node DT_NODELABEL(rtc) //RTC node
#define UART_DEVICE_NODE DT_NODELABEL(usart1) //Uart node
#define EEPROM_NODE DT_COMPAT_GET_ANY_STATUS_OKAY(zephyr_i2c-target-eeprom)

struct device *const uart_dev = DEVICE_DT_GET(UART_DEVICE_NODE);
static const struct device *const rtc_dev = DEVICE_DT_GET(rtc_device_node);

K_SEM_DEFINE(wifi_ready, 0, 1);  // Semaphore to signal Wi-Fi connection
K_SEM_DEFINE(wifi_fail, 0, 1);  // Semaphore to signal Wi-Fi connection
K_SEM_DEFINE(data_ready, 0, 1);      // Semaphore to signal data is ready for upload
K_SEM_DEFINE(upload_completed, 0, 1); // Semaphore to signal completed data upload
K_SEM_DEFINE(sleep_done, 0, 1); 




int connected = 0;
int backlogStart = 0;
int counterWrite = 0;
int firstCon = 1;


void timerInterrupt()
{
	k_sem_give(&sleep_done);
}

K_TIMER_DEFINE(timer3, timerInterrupt, NULL);


void sleepDevice() 
{	
	printk("TEST sleep\n");
	while(1)
	{
		if(firstCon==1)
		{
			k_sem_take(&wifi_ready, K_FOREVER);
			printk("Wifi connected first time\n");
			k_timer_start(&timer3, K_MSEC(0), K_SECONDS(60));
			firstCon = 0;
			// k_sem_give(&sleep_done);
			continue;
		}
		// printk("Waiting for upload Comleted\n\n\n\n\n\n\n\n");

		k_sem_take(&upload_completed, K_FOREVER);
		printk("Sleepdevice...\n");
		// k_sleep(K_SECONDS(5));
		
		
		// k_sem_give(&sleep_done);
	}
}

void wifi_connect() 
{
	printk("TEST wifi\n");
	while(1)
	{
		k_sem_take(&wifi_fail, K_FOREVER);

		char* resp;																	
        // resp = sendESP("AT+CWJAP=\"iPhone van Joey\",\"123456789\"\r\n", uart_dev, at);
		resp = sendESP("AT+CWJAP=\"vNoort\",\"Jol!no2020\"\r\n", uart_dev, at);
        // printk("%s", resp);
        k_sleep(K_MSEC(300));
        const char *lastFourCharacters = resp + strlen(resp) - strlen("FAIL\r\n");
        if(strcmp(lastFourCharacters, "FAIL\r\n") == 0)
        {
			if(firstCon == 1)
			{
				printk("FAIL on startup, trying again...\n");
				k_sem_give(&wifi_fail);
            	continue;
			}
			k_sem_give(&upload_completed);
			continue;
        }
		if(firstCon == 1)
		{
			resp = sendESP("AT+CIPSNTPCFG=1,1,\"0.nl.pool.ntp.org\"\r\n", uart_dev, at);
			// printk("%s", resp);
			k_sleep(K_MSEC(500));

			resp = sendESP("AT+CIPSNTPTIME?\r\n", uart_dev, at);						
			// printk("%s", resp);
			k_sleep(K_MSEC(200));
			parseTime(resp, rtc_dev);
			connected=1;
			k_sem_give(&wifi_ready);
		}
		else
		{
			connected=1;
			k_sem_give(&data_ready);
		}
	}
}

void eeprom_thread() {
	printk("TEST eeprom\n");

    while (1) {
		k_sem_take(&sleep_done, K_FOREVER);
        printk("EEPROM\n");
        // Perform EEPROM operations
		const struct device *sensor = DEVICE_DT_GET_ANY(bosch_bme280);
		struct sensor_value temp, press, humidity;
		int8_t * data[6];
		int8_t recieved;
		int32_t time = getEpochTime(rtc_dev);
		// printk("Time_t size: %d", sizeof(int64_t));
		printk("Returned time: %d\n", time);
		
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
		k_sleep(K_MSEC(10));
		for(int x = 0; x<6; x++)
		{
			writeEeprom(counterWrite,data[x]);
			counterWrite++;
			k_sleep(K_MSEC(10));
		}

		if(counterWrite > 14400)
		{
			counterWrite = 0;
		}

		if(connected == 0)
		{
			printk("Retry wifi connect\n");
			k_sem_give(&wifi_fail);
		}

        // Signal that data is ready for upload
        k_sem_give(&data_ready);
    }
}

void upload_thread() {
	printk("TEST upload\n");
	int32_t lastTime = 0;

	while(1)
	{
		// Wait for data to be ready for upload
		k_sem_take(&data_ready, K_FOREVER);
		uint8_t sent = 0;
		if(connected==0)
		{
			k_sem_give(&upload_completed);
			continue;
		}
		

		char* resp;
		resp = sendESP("AT\r\n", uart_dev, at);
		// printk("%s", resp);
		do
		{
			storageData data = returnStorageData(backlogStart);											//Needs correct index instead of just 0
			measurementStruct meas;

			if(data.time < lastTime)
			{
				lastTime += 60;
				meas = sendMeasurement(data.temp1,data.temp2, data.press1,data.press2, data.humid1,data.humid2, lastTime, uart_dev);
			}
			else
			{
				printk("Lasttime: %ld, this time: %ld\n", lastTime, data.time);
				meas = sendMeasurement(data.temp1,data.temp2, data.press1,data.press2, data.humid1,data.humid2, data.time, uart_dev);
				lastTime = data.time;
			}

			 
		printk("COUNTERWRITE: %d\n", counterWrite);
		printk("BACKLOGSTART: %d\n", backlogStart);
			
			resp = sendESP(meas.tcp, uart_dev, tcp);											//CIPSTART
			// printk("%s", resp);
			k_sleep(K_MSEC(500));
			const char *lastFourCharacters;
			lastFourCharacters = resp + strlen(resp) - strlen("ERROR\r\n");
			if(strcmp(lastFourCharacters, "ERROR\r\n") == 0)									//If it fails, connection must have been lost so jump out of do-while and sleep
			{
				connected = 0;
				printk("Upload failed\n");
				k_sem_give(&upload_completed);
				break;
			}

			resp = sendESP(meas.cipsend, uart_dev, tcp);										//CIPSEND=
			// printk("%s", resp);
			k_sleep(K_MSEC(200));
			lastFourCharacters = resp + strlen(resp) - strlen("ERROR\r\n");
			if(strcmp(lastFourCharacters, "ERROR\r\n") == 0)									//If it fails, connection must have been lost so jump out of do-while and sleep
			{
				connected = 0;
				printk("Upload failed\n");
				k_sem_give(&upload_completed);
				break;
			}
			else{//Successfull request
				resp = sendESP(meas.request, uart_dev, req);									//GET REQUEST
				lastFourCharacters = resp + strlen(resp) - strlen("ERROR\r\n");
				if(strcmp(lastFourCharacters, "ERROR\r\n") == 0)									//If it fails, connection must have been lost so jump out of do-while and sleep
				{
					connected = 0;
					printk("Upload failed\n");
					k_sem_give(&upload_completed);
					break;
				}
				// printk("%s", resp);
				
			}
			sent++;
			backlogStart += 10;
			if(backlogStart > 14400)
			{
				backlogStart = 0;
			}
			k_sleep(K_MSEC(100));
			resp = sendESP("AT+CIPCLOSE\r\n", uart_dev, at);	

		}while(backlogStart != counterWrite || sent > 47);

		if(connected != 0)
		{
			backlogStart = counterWrite;
			k_sem_give(&upload_completed);		
		}
	}
}


K_THREAD_DEFINE(wifi_connect_id, STACKSIZE_WIFI, wifi_connect, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(eeprom_thread_id, STACKSIZE_EEPROM, eeprom_thread, NULL, NULL, NULL, 5, 0, 0);
K_THREAD_DEFINE(upload_thread_id, STACKSIZE_UPLOAD, upload_thread, NULL, NULL, NULL, 7, 0, 0);
K_THREAD_DEFINE(waiting_thread_id, STACKSIZE_SLEEP, sleepDevice, NULL, NULL, NULL, 7, 0, 0);

// K_THREAD_STACK_DEFINE(wifi_connect_stack, STACKSIZE_WIFI);
// K_THREAD_STACK_DEFINE(eeprom_thread_stack, STACKSIZE);
// K_THREAD_STACK_DEFINE(upload_thread_stack, STACKSIZE);
// K_THREAD_STACK_DEFINE(waiting_thread_stack, STACKSIZE);

void main(void) {

	printk("TEST MAIN\n");
    if (!device_is_ready(uart_dev)) {
        printk("UART device not found!");
        return;
    }
	int ret = uart_irq_callback_user_data_set(uart_dev, readUsart, NULL);
    uart_irq_rx_enable(uart_dev);

	k_sem_give(&wifi_fail);
    // Wait forever
    k_sleep(K_FOREVER);
}

   