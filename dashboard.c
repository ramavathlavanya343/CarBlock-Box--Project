/*
 * File:   dashboard.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:17 PM
 */


#include <xc.h>
#include "main.h"

/*External variables used in the dashboard display*/
extern unsigned int speed;
extern unsigned short adc_reg_val;

void dashboard(unsigned char *gear[],unsigned int index)
{
    /*Display fixed labels on the first line of the dashboard*/
    clcd_print("Time",LINE1(0));
    clcd_print("Gear", LINE1(8));
    clcd_print("SP", LINE1(13));
    
    /*Display the current time on the dashboard*/
    display_time();
    
    /*Display the current gear based on the index provided*/
    clcd_print(gear[index], LINE2(9));
    
    /*Calculate the speed based on the ADC register value*/
    speed = ((adc_reg_val) / 10.23);
    if ( speed > 99)
    {
        speed = 99;
    }
    
    /*Display the calculated speed on the dashboard*/
    clcd_putch('0'+(speed / 10),LINE2(13));
    clcd_putch('0'+(speed % 10),LINE2(14));
}