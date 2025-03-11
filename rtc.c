/*
 * File:   rtc.c
 * Author: Reliance
 *
 * Created on 23 August, 2024, 2:01 PM
 */

#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"

 

//void rtc(void)
//{
////	init_config();
//
//	while (1)
//	{
//#if 1
//		get_time(); //fetch time from RTC
//		display_time();
//#else
//		get_date();  //data from from RTC
//		display_date();
//#endif
//	}
//}