/* 
 * File:   i2c.h
 * Author: Reliance
 *
 * Created on 22 August, 2024, 2:14 PM
 */

#ifndef I2C_H
#define	I2C_H

void init_i2c(void);
void i2c_start(void); //start the commu
void i2c_rep_start(void);
void i2c_stop(void);
void i2c_write(unsigned char data); //transefr
unsigned char i2c_read(void); //recvie

#endif	

