/* 
 * File:   eeprom.h
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:37 AM
 */

#ifndef EEPROM_H
#define EEPROM_H

void write_internal_eeprom(unsigned char address, unsigned char data); 
unsigned char read_internal_eeprom(unsigned char address);

#endif