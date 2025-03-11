/*
 * File:   store_event.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:22 PM
 */

#include <xc.h>
#include "main.h"

extern unsigned char time[9];
int event_count=0;
unsigned char store_add = 0x00;


/*
 * Function: store_event
 * ---------------------
 * Stores the current time, gear, and speed into the external EEPROM.
 *
 * gear: The current gear as a string
 * speed: The current speed as an integer
 *
 * This function increments the event counter, resets the storage address 
 * after 10 events, and writes the time, gear, and speed into the EEPROM.
 */

void store_event(unsigned char gear[],unsigned int speed)
{
    //logic for storing 
    event_count++;
    if(event_count == 10)
    {
        store_add=0x00;
    }
    int write_char=0;
    
    /*Write time and gear to EEPROM*/
    while(write_char <10)
    {
        if(write_char <8)
        {
           if(write_char !=2 && write_char !=5)
           {
               write_external_eeprom(store_add,time[write_char]);
               store_add++;
           }
        } 
        else if(write_char < 9)       
        {
            write_external_eeprom(store_add,gear[0]);
            store_add++;
            write_external_eeprom(store_add,gear[1]);
            store_add++;
        }
        write_char++;  
    }
    write_external_eeprom(store_add,(speed / 10) + '0');
    store_add++;
    write_external_eeprom(store_add,(speed % 10) + '0');
    store_add++;       
}