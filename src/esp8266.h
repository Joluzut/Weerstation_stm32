#ifndef esp8266_H_
#define esp8266_H_

#include <zephyr/kernel.h>
// #include <zephyr/devicetree.h>
#include <zephyr/device.h>
#include <zephyr/drivers/uart.h>
#include <string.h>
#include <stdio.h>
#include <time.h>



#define MSG_SIZE 512
typedef enum{
    rst=0,
    at,
    tcp,
    req
}status;
typedef struct
{
    char* tcp;
    char* cipsend;
    char* request;
}measurementStruct;



 
static char rx_buf[MSG_SIZE];
static int rx_buf_pos = 0;

void send_str(const struct device *dev, const char *str);
measurementStruct sendMeasurement(int temp1, int temp2, int press1, int press2, int humid1, int humid2, int32_t timestamp, const struct device *uart_dev);
void readUsart();
char* returnUsartStr(status stat);

char* sendESP(const char* str, const struct device *uart_dev, status stat);
char* getNTPTime();

#endif 
