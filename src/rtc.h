

#ifndef RTC_H_
#define RTC_H_

#include <zephyr/drivers/rtc.h>
#include <zephyr/drivers/counter.h>
#include "time.h"
#define rtc_device_node DT_NODELABEL(rtc)


static const struct device *getRtc(void);
void syncRTC(const char* time, const struct device *dev, struct tm *timeStruct);
time_t getEpochTime(const struct tm *timeStruct);

#endif 
