#ifndef EEPROM_H_
#define EEPROM_H_
#include <stdio.h>
#include <stdint.h>
#include <time.h>

typedef struct 
{
    int8_t temp1;
    int8_t temp2;
    int8_t press1;
    int8_t press2;
    int8_t humid1;
    int8_t humid2;
    int32_t time;
}storageData;

storageData returnStorageData(int counter);
void writeEeprom( int counter, int8_t data );
void writeBigEeprom( int counter, int32_t data);
int8_t readEeprom( int counter);
int32_t readBigEeprom( int counter);

#endif /* EEPROM_H_ */