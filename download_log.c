/*
 * File:   download_log.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:19 PM
 */


#include <xc.h>
#include "main.h"
#include "uart.h"

extern int view_flag, event_count;
int count = 0;
extern char main_f;
int add = 0x00;

/*Function to download the event log and send it via UART*/
void download_log()
{
    /*Display a message indicating successful log download*/
    clcd_print("DOWNLOADED LOG", LINE1(0));
    clcd_print("SUCCESSFULLY", LINE2(0));
   
    /*Adjust the EEPROM address offset if viewing the log from a specific point*/
    if ( view_flag > 0)
    {
        add = add + ( (event_count % 10) * 10);
        view_flag = 0;
    }
    
    /*Send the log header via UART*/
    puts("#TIME    GEAR SP");
    
    /*Loop through and download up to 10 events, sending them via UART*/
    while((count < event_count) && (count < 10))
    {
        puts("\n\r");
        putch(count + '0');
        putch(' ');
        download_display(add);
        if ( add < 90)
        {
            add = add + 10;
        }
        else 
        {
            add = 0x00;
        }
        count++;
    }
    
    for (unsigned long int i = 5000; i--;);
    main_f = MENU;
    count = 0;
    add = 0x00;
    CLEAR_DISP_SCREEN;
    return;
}

/*Function to retrieve and format log data from EEPROM and send it via UART*/
void download_display(int address)
{
    int i=0;
    char data[100];
    unsigned char ch;
    
    while (i < 16)
    {
        if (i == 2 || i == 5)  
        {
            data[i] = ':';
        } 
        else if (i == 8 || i == 11) 
        {
            data[i] = ' ';
        } 
        else
        {
            ch = read_external_eeprom(address++);
            data[i] = ch;
        }
        i++;
    }
    data[i] = '\0';
    puts(data);
}
