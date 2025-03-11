/*
 * File:   set_time.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:21 PM
 */


#include <xc.h>
#include "main.h"
#include "ds1307.h"
#include "matrix_keypad.h"

extern unsigned char clock_reg[3];
extern unsigned char time[9];
unsigned char Time[9];
unsigned char minute;
unsigned char hr;
unsigned char second;
unsigned int set_flag;
extern char main_f ;
unsigned char dummy;
unsigned int set_count;
unsigned int set_delay;

/*Function to handle the process of setting the time*/
void settime(char key) 
{
    //logic for set time
    dummy = read_ds1307(SEC_ADDR);
    write_ds1307(SEC_ADDR, dummy | 0x80);
    clcd_print("ENTER SET TIME", LINE1(0));
    
    if (set_flag == 0) 
    {
        for (unsigned int i = 0; i < 9; i++) 
        {
            Time[i] = time[i];
        }
        /*clock_reg to binary and assign to hr, minute, and second*/
        hr = (((clock_reg[0] >> 4) & 0x03)*10) + (clock_reg[0] & 0x0F);
        minute = ((clock_reg[1] >> 4)*10)+(clock_reg[1] & 0x0F);
        second = ((clock_reg[2] >> 4)*10)+(clock_reg[2] & 0x0F);
        set_flag = 1;
    }
    /*Handle key press for selecting which field (hour, minute, second) to set*/
    if(key==MK_SW12)
    {
        set_count++;
        if(set_count==3)
        {
            set_count=0;
        }    
    }

    /*Handle key press for incrementing the value of the selected field*/
    if(key==MK_SW11)
    {
        if(set_count==0)
        {
            second++;
            if(second==60)
            {
                second=0;
            }
        }
        else if(set_count==1)
        {
            minute++;
            if(minute==60)
            {
                minute=0;
            }
        }
        else if(set_count==2)
        {
            hr++;
            if(hr==24)
            {
                hr=0;
            }
        }
        
    }
    /*Handle long press on MK_SW11 to confirm and save the set time*/
   if(key==MK_LONG_SW11)
    {
       /*Convert the time values back to BCD format and write to DS1307*/
        clock_reg[0]=((hr/10)<<4)|(hr%10);
        clock_reg[1]=((minute/10)<<4)|(minute%10);
        clock_reg[2]=((second/10)<<4)|(second%10);
    
        write_ds1307(HOUR_ADDR, clock_reg[0]);
        write_ds1307(MIN_ADDR, clock_reg[1]);
        write_ds1307(SEC_ADDR, clock_reg[2]);
        
        set_count==0,set_flag == 0,set_delay=0;
        main_f=MENU;
        CLEAR_DISP_SCREEN;
        for(unsigned long int wait=1000000;wait--;);
        unsigned char dummy = read_ds1307(SEC_ADDR);
	    write_ds1307(SEC_ADDR, dummy & 0x7F); 
        return;
    }
    
    
   /*Handle long press on MK_SW12 to cancel the time setting and return to the menu*/
    if(key==MK_LONG_SW12)
    {
        main_f=MENU;
        set_count==0,set_flag == 0,set_delay=0;
        CLEAR_DISP_SCREEN;
        for(unsigned long int wait=1000000;wait--;);
        unsigned char dummy = read_ds1307(SEC_ADDR);
	    write_ds1307(SEC_ADDR, dummy & 0x7F); 
        return;
    }
     
    if(set_count==0)
    {
        blink_second_field();
    }
    else if(set_count==1)
    {
        blink_minute_field();
    }
    else if(set_count==2)
    {
        blink_hr_field();
    }

}

/*Function to blink the seconds field during time setting*/
void blink_second_field()
{
    set_delay++;
    if(set_delay==200)
    {
        Time[6]='0'+(second/10);
        Time[7]='0'+(second%10);
        
        Time[3]='0'+(minute/10);
        Time[4]='0'+(minute%10);
        
    }
    else if(set_delay==400)
    {
        set_delay=0;
         Time[6]='_';
         Time[7]='_';
                     
    }
    display_set_time();
}

/*Function to blink the minutes field during time setting*/
void blink_minute_field()
{
    set_delay++;
    if(set_delay==200)
    {
        Time[3]='0'+(minute/10);
        Time[4]='0'+(minute%10);
        
        Time[6]='0'+(second/10);
        Time[7]='0'+(second%10);
        
    }
    else if(set_delay==400)
    {
         set_delay=0;
         Time[3]='_';
         Time[4]='_';
                     
    }
    display_set_time();
    
}
/*Function to blink the hours field during time setting*/
void blink_hr_field()
{
    set_delay++;
    if(set_delay==200)
    {
        Time[0]='0'+(hr/10);
        Time[1]='0'+(hr%10);
        
        Time[3]='0'+(minute/10);
        Time[4]='0'+(minute%10);
        
    }
    else if(set_delay==400)
    {
         set_delay=0;
         Time[0]='_';
         Time[1]='_';
                     
    }
    display_set_time();   
}
/*Function to display the current time being set on the CLCD*/
void display_set_time()
{
    clcd_print(Time,LINE2(0));
}


