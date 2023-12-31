#include <zephyr/drivers/rtc.h>
// #include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/counter.h>
#include "time.h"

typedef struct tm parsed_time;

int32_t getEpochTime(const struct device *dev);
void parseTime(char* response, const struct device *rtc);
