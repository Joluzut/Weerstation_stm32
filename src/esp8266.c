#include "esp8266.h"
K_MSGQ_DEFINE(uart_msgq, 2, 128, 4);
char send_buf[256];


char* sendESP(const char* str, const struct device *uart_dev)
{
    snprintf(send_buf, 64, "AT+CIPSNTPTIME?\r\n");
    send_str(uart_dev, send_buf);

    return returnUsartStr();
}

char* getNTPTime()
{
    char* time;

    return time;
}

char* returnUsartStr()
{
    int ret;
    uint16_t c;
    rx_buf_pos = 0;
    for(int i = 0; i< sizeof(rx_buf); i++)
    {
        rx_buf[i] = '\0';
    }
    while(1)
    {
        ret = k_msgq_get(&uart_msgq, &c, K_FOREVER);
        if (ret == 0) {
            // printk("Received: %c\n", uart_data);
            rx_buf[rx_buf_pos] = c;
            rx_buf_pos++;
        }
        char* check = "OK\r\n";
        const char *lastFourCharacters = rx_buf + strlen(rx_buf) - strlen("OK\r\n");
        if(strcmp(check, lastFourCharacters) == 0)
        {
            return rx_buf;
        }
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