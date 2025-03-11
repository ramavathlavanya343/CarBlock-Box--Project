/*
 * File:   clear_log.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:18 PM
 */



#include <xc.h>
#include "main.h"

extern char main_f;
extern int event_count;
unsigned char address;

void clear_log(char key)
{
    //logic for clear
    clcd_print("CLEARED LOG", LINE1(0));
    clcd_print("SUCCESSFULLY", LINE2(0));
    event_count = 0;
    address = 0x00;
    for(unsigned long int i = 1000000; i--; );
    CLEAR_DISP_SCREEN;
    main_f = MENU;
    
}