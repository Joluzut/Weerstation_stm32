#include "rtc.h"

void syncRTC(const char* time, const struct device *dev, struct tm *timeStruct)//Sync RTC to time given as string
{
    if (strptime(time, "%a %b %d %H:%M:%S %Y", timeStruct) == NULL) {
        printk("Failed to parse string");
        return;
    }

    rtc_set_time(dev, timeStruct);
}

void parseTime(char* response, const struct device *rtc)
{
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
    int day, year, hours, minutes, seconds;

    // Parse the response string and extract date and time components
    int parsed_items = sscanf(response, "+CIPSNTPTIME:%3s %3s %d %d:%d:%d %d\r\n",
                              parsed_time.tm_wday, month, &parsed_time.tm_mday,
                              &hours, &minutes, &seconds, &year);

    // Convert the month abbreviation to month number
    const char* months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
                            "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    for (int i = 0; i < 12; ++i) {
        if (strcmp(month, months[i]) == 0) {
            parsed_time.tm_mon = i;
            break;
        }
    }

    // Adjust year (assuming 1900-based year count)
    parsed_time.tm_year = year - 1900;

    // Set remaining time components
    parsed_time.tm_hour = hours;
    parsed_time.tm_min = minutes;
    parsed_time.tm_sec = seconds;
    printk("Parsed seconds: %d", parsed_time.tm_sec);
    printk("Parsed Date and Time: %s", asctime(&parsed_time));

    rtc_set_time(rtc, &parsed_time);
}

time_t getEpochTime(const struct device *dev)
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
    time_t epochTime = mktime(&timeStruct);

    if (epochTime == -1) {
        printk("Failed to convert time to Epoch time\n");
        return NULL;
    }
    return epochTime;
}
