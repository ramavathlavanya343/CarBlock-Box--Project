/*
 * File:   main.c
 * Author: Reliance
 * Created on 9 August, 2024, 2:16 PM
 */


#include <xc.h>
#include "main.h"

/*Global variables*/
unsigned int flag = 0;
char main_f = 0, menu_f = 0;
unsigned int speed;
unsigned short adc_reg_val;
unsigned char *gear[] = {"ON", "GR", "GN", "G1", "G2", "G3", "G4", "G5", "C "};
unsigned char key;
unsigned int index = 0;
unsigned char clock_reg[3];
unsigned char time[9];

/*Function to display time on the second line of the CLCD*/
void display_time(void)
{
	clcd_print(time, LINE2(0));
}

/* Function to get the current time from DS1307 and format it into a string*/
void get_time(void)
{
    /*Read current time from DS1307 registers*/
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

    /*Check if the clock is in 12-hour format*/
	if (clock_reg[0] & 0x40) //bit is set to 1 12 hrs format 
	{
        /*Format hours for 12-hour format*/
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01); 
		time[1] = '0' + (clock_reg[0] & 0x0F); 
	}
	else  //24 hrs format
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);     
	} 
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

/*Function to initialize various peripherals and modules*/
void init_config(void)
{
	init_clcd();
	init_i2c();
	init_ds1307();
    init_adc();
    init_matrix_keypad();
    init_timer0();
    PEIE = 1;
}

void main(void) {

    init_config();
    char pass_addr = 100;
    
    while (1) {
        
        /*
         * get the time 
         * based on switch press change the event
         * Read switches and ADC value
         */

       
        key = read_switches(LEVEL_CHANGE);
        adc_reg_val = read_adc(CHANNEL4);
        get_time();

        if (key == MK_SW1) 
        {
            /*increment the gear*/
            index++;
            store_event(gear[index],speed);

            if (index >= 8) {
                index = 7;
            }
           
        } 
        else if (key == MK_SW2)
        {
            /*decrement the gear*/
            index--;
            store_event(gear[index],speed);
            if (index <= 1) {
                index = 1;
            }

        } 
        else if (key == MK_SW3) 
        
        {
            CLEAR_DISP_SCREEN;
            store_event(gear[index],speed);
            index = 8;
            flag = 1;

        }

        if (main_f == DASHBOARD)
        {
            dashboard(gear,index);
            if (  !flag )
            {
                flag = 1;
                store_event(gear[index],speed);
            }
            /*Check for switch press to move to PASSWORD screen*/
            if (key == MK_SW11) 
            {
                CLEAR_DISP_SCREEN;
                main_f = PASSWORD;
            }
        } 
        else if (main_f == PASSWORD) 
        {
            password(key);
        } 
        
        else if (main_f == MENU) {
                menu(key);
        } else if (main_f == MENU_ENTER) {

            /*Handle different menu options based on menu_f*/
            if (menu_f == 0) {
                 view_log(key);
            } else if (menu_f ==2) {
               
                /*Download log via UART*/
                GIE = 0, PEIE = 0;
                init_uart();
                download_log();
                TXIE = 0;
                GIE = 1, PEIE = 1;
                
            } else if (menu_f == 1) {
                 clear_log(key);
            } else if (menu_f == 3) {
                settime(key);
            } else if (menu_f == 4) {

                change_pass(key);
            }
        }

    }
    
}
