#ifndef esp8266_H_
#define esp8266_H_

#include <zephyr/kernel.h>
// #include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
// #include <string.h>
// #include <stdio.h>
// #include <time.h>


#define MSG_SIZE 128




 
static char rx_buf[MSG_SIZE];
static int rx_buf_pos = 0;


void readUsart();
char* returnUsartStr();

char* sendESP(const char* str, const struct device *uart_dev);
char* getNTPTime();

#endif 
