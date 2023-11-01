#include "rtc.h"

void syncRTC(const char* time, const struct device *dev, struct tm *timeStruct)//Sync RTC to time given as string
{
    if (strptime(time, "%a %b %d %H:%M:%S %Y", timeStruct) == NULL) {
        printk("Failed to parse string");
        return;
    }

    rtc_set_time(dev, timeStruct);
}

time_t getEpochTime(const struct device *dev, const struct tm *timeStruct)
{
    // Convert the parsed time to Epoch time
    rtc_get_time(dev, timeStruct);
    time_t epochTime = mktime(timeStruct);

    if (epochTime == -1) {
        printk("Failed to convert time to Epoch time\n");
        return NULL;
    }
    return epochTime;
}

int returnOne()
{
    return 1;
}