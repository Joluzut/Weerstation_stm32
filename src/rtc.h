#include <zephyr/drivers/rtc.h>
// #include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/counter.h>
#include "time.h"



void syncRTC(const char* time, const struct device *dev, struct tm *timeStruct);
time_t getEpochTime(const struct device *dev);
void parseTime(char* response, const struct device *rtc);
