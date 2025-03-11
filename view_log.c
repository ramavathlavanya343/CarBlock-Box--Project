/*
 * File:   view_log.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:22 PM
 */


#include <xc.h>
#include "main.h"

extern char main_f;
extern unsigned int current_item, flag2;
extern int event_count;
int count = 0, view_flag = 0;
int add = 0x00;


/*
 * Function: view_log
 * ------------------
 * Displays the stored log data on the CLCD, allowing the user to scroll through the logs.
 *
 * key: The key pressed by the user to interact with the log view.
 *
 * This function handles the scrolling and displaying of stored event logs.
 * The logs can be scrolled up and down using keys, and the function returns to the menu on a long press.
 */

void view_log(char key)
{
    
    if (event_count != 0) 
    {
        if ( !view_flag)
        {
            if ( event_count > 10)
            {
                add = add + ((event_count%10)*10);
                view_flag = 1;
            }

        }
        if (key == MK_SW11 && (count < (event_count - 1)) && count != 9) 
        {

            if (add < 90)
            {
                add = add + 10;                
            }
            else
            {
                add = 0x00;
            }
            count++;
        }

        if (key == MK_SW12 && count > 0) 
        {

            if (add > 9)
            { 
                add = add - 10;               
            }
            else 
            {
                add = 0x5A;
            }
            count--;
        }
        log_display(add);
    } 
    else 
    {
        clcd_print("NO LOGS ARE", LINE1(0));
        clcd_print("AVAILABLE", LINE2(0));
    }
    if (key == MK_LONG_SW12) 
    {
        CLEAR_DISP_SCREEN;
        main_f = MENU;
        current_item = 0;
        flag2 = 0;
        count = 0;
        add = 0x00;
        for (unsigned long int k = 400000; k--;);
        return;
    }
}

/*
 * Function: log_display
 * ---------------------
 * Displays a single log entry from the EEPROM on the CLCD.
 *
 * address: The starting address in the EEPROM from which to read the log entry.
 *
 * This function reads the time, gear, and speed from the EEPROM and displays them on the CLCD.
 */

void log_display(int address) 
{
    unsigned char ch;
    int i = 0;
    
    clcd_print("#TIME    GEAR SP", LINE1(0));
    while (i < 16)
    {
        if ( i == 0)
        {
            clcd_putch('0'+count,LINE2(i));
        }
        else if ( i == 1)
        {
            clcd_putch('.',LINE2(i));
        }
        else if (i == 4 || i == 7) 
        {
            clcd_putch(':', LINE2(i));
        } 
        else if (i == 10 || i == 13) 
        {
            clcd_putch(' ', LINE2(i));
        } 
        else
        {
            ch = read_external_eeprom(address++);
            clcd_putch(ch, LINE2(i));
        }
        i++;
    }
}