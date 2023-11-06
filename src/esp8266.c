#include "esp8266.h"

K_MSGQ_DEFINE(uart_msgq, 2, 270, 4);
char send_buf[256];

void send_str(const struct device *dev, const char *str) {
    int msg_len = strlen(str);
    
    printk("Device %s sending: \"%s\"\n", dev->name, str);
    for (int i = 0; i < msg_len; i++) {
        uart_poll_out(dev, str[i]);
    }
 
}

measurementStruct sendMeasurement(int temp1, int temp2, int press1, int press2, int humid1, int humid2, time_t timestamp, const struct device *uart_dev)
{
    measurementStruct meas;
    meas.tcp = "AT+CIPSTART=\"TCP\",\"joey.lvannoort.com\",80\r\n";

    struct tm *timeInfo = localtime(&timestamp);
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

char* sendESP(const char* str, const struct device *uart_dev, status stat)
{
    
    snprintf(send_buf, 200, str);
    send_str(uart_dev, send_buf);
    
    return returnUsartStr(stat);
}

char* getNTPTime()
{
    char* time;

    return time;
}

char* returnUsartStr(status stat)
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

   

    switch(stat)
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
        case req:
            check = "OK\r\n";
            check2 = "WIFI DISCONNECT\r\n";
            check3 = "ERROR\r\n";


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

        
        // check = "OK\r\n";
        // char* check = "OK\r\n";

        const char *lastFourCharacters = rx_buf + strlen(rx_buf) - strlen(check);
        const char *lastFourCharacters2 = rx_buf + strlen(rx_buf) - strlen(check2);
        const char *lastFourCharacters3 = rx_buf + strlen(rx_buf) - strlen(check3);

        // printk("last4char: %s\n", lastFourCharacters2);

        if(strcmp(check, lastFourCharacters) == 0)
        {
            if(stat == req)
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
        // else
        // {
        //     printk("None");
        // }
    }
}

void readUsart(const struct device *uart_dev, void *user_data)
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



// char* check_buff;
// if((c == 'O' || c == 'K' || c == '\r' || c=='\n') && rx_buf_pos > 0)
// {
//     const char* check = "OK\r\n";
//     strcat(check_buff, c);
//     if(strcmp(check_buff, check) == 0)
//     {
//         //end reading
//     }
// }
// else
// {
//     check_buff = '\0';
// }

// check_buff == check && index = 4