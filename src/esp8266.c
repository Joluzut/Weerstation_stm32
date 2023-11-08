#include "esp8266.h"

K_MSGQ_DEFINE(uart_msgq, 2, 270, 4);
char send_buf[256];

void send_str(const struct device *dev, const char *str) {  //This functions sends the string over uart
    int msg_len = strlen(str);
    
    printk("Device %s sending: \"%s\"\n", dev->name, str);
    for (int i = 0; i < msg_len; i++) {
        uart_poll_out(dev, str[i]);
    }
 
}

measurementStruct sendMeasurement(int temp1, int temp2, int press1, int press2, int humid1, int humid2, int32_t timestamp, const struct device *uart_dev)   //This will return a struct containing strings to send to the ESP
{
    measurementStruct meas;
    meas.tcp = "AT+CIPSTART=\"TCP\",\"joey.lvannoort.com\",80\r\n"; //This command is consistent
    time_t convertedTime = (time_t)timestamp;
    struct tm *timeInfo = localtime(&convertedTime);
    char formattedDate[25]; // Buffer to hold the formatted time string
    char formattedTime[25]; // Buffer to hold the formatted time string

    strftime(formattedDate, sizeof(formattedDate), "%Y-%m-%d", timeInfo);
    strftime(formattedTime, sizeof(formattedTime), "%H:%M:%S", timeInfo);

    // printk("%s%%20%s\n", formattedDate, formattedTime);

    char request[500]; // Make sure the buffer is large enough to hold the formatted string
    snprintf(request, sizeof(request), "GET /weerstation_get.php?api_key=tPmAT5Ab3j7F9&temp=%d.%d&press=%d.%d&humid=%d.%d&timestamp=%s%%%%20%s HTTP/1.1\r\nHost: joey.lvannoort.com\r\n\r\n", temp1, temp2, press1, press2, humid1, humid2,formattedDate, formattedTime);
    meas.request = request;         
    // printk("Request: %s\n", request);
    char* requestsize[16];
    snprintf(requestsize,sizeof(requestsize),"AT+CIPSEND=%d\r\n", (strlen(request)-1));
    meas.cipsend=requestsize;
    return meas;
}

char* sendESP(const char* str, const struct device *uart_dev, status stat)//Send string to ESP and return the response
{
    
    snprintf(send_buf, 200, str);
    send_str(uart_dev, send_buf);
    
    return returnUsartStr(stat);
}

char* returnUsartStr(status stat)   //put characters from messagequeue into string and return it
{
    int ret;
    uint8_t ok = 0;
    uint16_t c;
    rx_buf_pos = 0;
    for(int i = 0; i< sizeof(rx_buf); i++)
    {
        rx_buf[i] = '\0';
    }
    char* check;
    char* check2;
    char* check3;

   

    switch(stat)    //Different commands can get different responses, the enum shows what responses it is expecting
    {
        case rst:
            check = "WIFI DISCONNECT\r\n";
            check2 = "WIFI GOT IP\r\n";
            break;
        case at:
            check = "OK\r\n";
            check2 = "FAIL\r\n";
            break;
        case tcp:
            check = "OK\r\n";
            check2 = "ERROR\r\n";
            break;
        case req:
            check = "OK\r\n";
            check2 = "WIFI DISCONNECT\r\n";
            check3 = "ERROR\r\n";
            break;
    }
   
    while(1)
    {
        ret = k_msgq_get(&uart_msgq, &c, K_FOREVER);
        printk("%c", c);
        if (ret == 0) {
            // printk("Received: %c\n", uart_data);
            rx_buf[rx_buf_pos] = c;
            rx_buf_pos++;
        }

        const char *lastFourCharacters = rx_buf + strlen(rx_buf) - strlen(check);
        const char *lastFourCharacters2 = rx_buf + strlen(rx_buf) - strlen(check2);
        const char *lastFourCharacters3 = rx_buf + strlen(rx_buf) - strlen(check3);

        if(strcmp(check, lastFourCharacters) == 0)
        {
            if(stat == req) //A sucessfull request will send back OK\r\n 3 times. So the response is received completely this way.
            {
                ok++;
                if(ok==3)
                {
                    return rx_buf;
                }
            }
            else
            {
                return rx_buf;
            }
        }
        else if(strcmp(check2, lastFourCharacters2) == 0)
        {
            return rx_buf;
        }
        else if(strcmp(check3, lastFourCharacters3) == 0)
        {
            return rx_buf;
        }
    }
}

void readUsart(const struct device *uart_dev, void *user_data)//The usart interrupt calss this function and will put the character into the messagequeue
{
    int ret;
    uint16_t c;
    
    ret = uart_poll_in(uart_dev, &c);
    if (ret == 0) {
        
        ret = k_msgq_put(&uart_msgq, &c, K_NO_WAIT);
        if (ret != 0) {
            printk("Failed to put data into message queue\n");
        }
        

    } else if (ret == -EAGAIN) {
        // No data available, handle it accordingly
    } else {
        // Handle error, if any
        printk("UART read error: %d\n", ret);
    }
}

