/*
 * File:   ds1307.c
 * Author: Reliance
 *
 * Created on 22 August, 2024, 2:39 PM
 */

#include "main.h"
#include "ds1307.h"
#include "i2c.h"
#include <xc.h>

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */

/*
 * disable the oscillater
 * set format
 * set the controler
 * enble the oscillater
 */
void init_ds1307(void) {
    unsigned char dummy;

    /* Setting the CH bit of the RTC to Stop the Clock */
    dummy = read_ds1307(SEC_ADDR); //it holds the sec value 
    write_ds1307(SEC_ADDR, dummy | 0x80);

    /* Seting 12 Hr Format */
    dummy = read_ds1307(HOUR_ADDR); //it holds the hrs value 
    write_ds1307(HOUR_ADDR, dummy | 0x40);

    /* 
     * Control Register of DS1307
     * 
     * Bit 7 - OUT
     * Bit 6 - 0
     * Bit 5 - OSF
     * Bit 4 - SQWE
     * Bit 3 - 0
     * Bit 2 - 0
     * Bit 1 - RS1
     * Bit 0 - RS0
     * 
     * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
     */
    write_ds1307(CNTL_ADDR, 0x93);

    /* Clearing the CH bit of the RTC to Start the Clock */
    dummy = read_ds1307(SEC_ADDR);
    write_ds1307(SEC_ADDR, dummy & 0x7F);

}

/*
 * 
 */
void write_ds1307(unsigned char address, unsigned char data) {
    i2c_start(); //calling i2c fun strst the communication
    i2c_write(SLAVE_WRITE); //sending uniq id
    i2c_write(address); //send address
    i2c_write(data); //send data 
    i2c_stop(); // stop commu
}

unsigned char read_ds1307(unsigned char address) {
    unsigned char data;

    i2c_start();
    i2c_write(SLAVE_WRITE); //pass unique ID
    i2c_write(address); //pass the address
    i2c_rep_start(); //start the communication
    i2c_write(SLAVE_READ); //pass the data
    data = i2c_read();
    i2c_stop();

    return data;
}