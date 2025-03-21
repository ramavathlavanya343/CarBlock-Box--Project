/* 
 * File:   External_eeprom.h
 * Author: Reliance
 *
 * Created on 22 August, 2024, 1:55 PM
 */

#ifndef external
#define external

#define SLAVE_READ_E		0xA1
#define SLAVE_WRITE_E		0xA0


void write_external_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_external_eeprom(unsigned char address1);

#endif
