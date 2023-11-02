#ifndef esp8266_H_
#define esp8266_H_

#include <zephyr/kernel.h>
// #include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
// #include <string.h>
// #include <stdio.h>
// #include <time.h>


#define MSG_SIZE 512
typedef enum{
    rst=0,
    at
}status;



 
static char rx_buf[MSG_SIZE];
static int rx_buf_pos = 0;


void readUsart();
char* returnUsartStr(status stat);

char* sendESP(const char* str, const struct device *uart_dev, status stat);
char* getNTPTime();

#endif 
