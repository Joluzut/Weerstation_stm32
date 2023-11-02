#ifndef EEPROM_H_
#define EEPROM_H_
#include <stdio.h>
#include <stdint.h>

void writeEeprom( int counter, int8_t data );
void writeBigEeprom( int counter, int32_t data);
int8_t readEeprom( int counter);
int32_t readBigEeprom( int counter);

#endif /* EEPROM_H_ */