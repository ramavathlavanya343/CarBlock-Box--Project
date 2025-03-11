/*
 * File:   i2c.c
 * Author: Reliance
 *
 * Created on 26 August, 2024, 12:03 PM
 */


#include <xc.h>

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_idle(void)
{
	while (!SSPIF);   //  0 not completed commu 1 means completed high 
	SSPIF = 0;
}

void i2c_ack(void)
{
	if (ACKSTAT)  //  optional
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void)
{
	SEN = 1; //stsrt the communication SEN =1 
	i2c_idle();
}

void i2c_stop(void) 
{
	PEN = 1;  //stop the communication
	i2c_idle();
}

void i2c_rep_start(void) //initiate the repeate RSEN=1
{
	RSEN = 1; //repeate the operation
	i2c_idle();
}

void i2c_write(unsigned char data)
{
	SSPBUF = data;  //transmit the data load the data to buffre reg
	i2c_idle();
}

void i2c_rx_mode(void)  //recevie 
{
	RCEN = 1; //enable the receive the operation
	i2c_idle(); //check the operation
}

void i2c_no_ack(void) //no ack
{
	ACKDT = 1; // no ack
	ACKEN = 1; //enable the  ack
}

unsigned char i2c_read(void)  //read the data from slave
{
	i2c_rx_mode();  //receive mode 
	i2c_no_ack();   //no ack

	return SSPBUF; //buffer reg
}
