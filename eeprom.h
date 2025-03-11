/* 
 * File:   eeprom.h
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:11 PM
 */

#ifndef EEPROM_H
#define	EEPROM_H

void write_internal_eeprom(unsigned char address, unsigned char data); 
unsigned char read_internal_eeprom(unsigned char address);


#endif	/* EEPROM_H */

