#include "rtc.h"

static const struct device *getRtc(void)//Configure the RTC device
{
	static const struct device *const dev = DEVICE_DT_GET(rtc_device_node);
	if (dev==NULL)
	{
		printk("Device not found\n");
		return NULL;
	}
	if(!device_is_ready(dev))
	{
		printk("Device not ready\n");
		return NULL;
	}

	printk("Found device.");
	return dev;
}

void syncRTC(const char* time, const struct device *dev, struct tm *timeStruct)//Sync RTC to time given as string
{
    if (strptime(time, "%a %b %d %H:%M:%S %Y", timeStruct) == NULL) {
        printk("Failed to parse string");
        return;
    }

    rtc_set_time(dev, timeStruct);
}

time_t getEpochTime(const struct tm *timeStruct)
{
    // Convert the parsed time to Epoch time
    time_t epochTime = mktime(timeStruct);

    if (epochTime == -1) {
        printk("Failed to convert time to Epoch time\n");
        return NULL;
    }
    return epochTime;
}
