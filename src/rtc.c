#include "rtc.h"

void parseTime(char* response, const struct device *rtc)//Parse string to Sync RTC
{
    printk("Received time: %s\n", response);
    struct tm parsed_time = {
        .tm_year = 2023-1900,
        .tm_mon = 10,
        .tm_mday = 1,
        .tm_hour = 12,
        .tm_min = 0,
        .tm_sec = 0,
        .tm_wday = 3,
    };
    char month[4];
    char wday[4];
    int day, year, hours, minutes, seconds;

    // Parse the response string and extract date and time components
    int parsed_items = sscanf(response, "AT+CIPSNTPTIME?\r\n+CIPSNTPTIME:%3s %3s %d %d:%d:%d %d\r\nOK\r\n",
                              wday, month, &parsed_time.tm_mday,
                              &hours, &minutes, &seconds, &year);

    // // Convert the month abbreviation to month number
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    const char* wdays[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"}; //Even though they are not necessary, they are stored because they are different in a request so could cause for issues in unexpected scenarios

    for (int i = 0; i < 12; ++i) {
        if (strcmp(month, months[i]) == 0) {
            parsed_time.tm_mon = i;
            break;
        }
        if(i < 7)
        {
            if(strcmp(wday, wdays[i]) == 0)
            {
                parsed_time.tm_wday = i+1;
                break;
            }
        }
    }

    // // Adjust year (assuming 1900-based year count)
    parsed_time.tm_year = year - 1900;

    // // Set remaining time components
    parsed_time.tm_hour = hours;
    parsed_time.tm_min = minutes;
    parsed_time.tm_sec = seconds;
    // printk("Parsed seconds: %d", parsed_time.tm_sec);
    rtc_set_time(rtc, &parsed_time);
    rtc_get_time(rtc, &parsed_time);
    printk("Parsed Date and Time: %s", asctime(&parsed_time));
}

int32_t getEpochTime(const struct device *dev)//Return epoch time from RTC
{
    struct tm timeStruct = {
        .tm_year = 2023-1900,
        .tm_mon = 10,
        .tm_mday = 1,
        .tm_hour = 12,
        .tm_min = 0,
        .tm_sec = 0
    };
    // Convert the parsed time to Epoch time
    rtc_get_time(dev, &timeStruct);
    int32_t epochTime = mktime(&timeStruct);

    if (epochTime == -1) {
        printk("Failed to convert time to Epoch time\n");
        return NULL;
    }
    // printk("Test\n");
    return epochTime;
}
