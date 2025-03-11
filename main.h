/* 
 * File:   main.h
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:12 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include "adc.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"
#include "eeprom.h"
#include "matrix_keypad.h"
#include "timer.h"
#include "External_eeprom.h"


#define DASHBOARD               0
#define PASSWORD                1
#define MENU                    2
#define MENU_ENTER              3
#define VIEWLOG                 0
#define DOWNLOADLOG             1
#define CLEARLOG                2
#define SETTIME                 3
#define CHANGEPASS              4

void dashboard(unsigned char *gear[], unsigned int index);               
void store_event(unsigned char gear[],unsigned int speed);
void password(char key);
void menu(char key);
void view_log(char key);
void download_log();
void clear_log(char key);
void settime(char key);
void change_pass(char key);
void display_time(void);
void log_display(int address);
void init_uart(void);
void download_display(int address);
void blink_second_field();
void blink_minute_field();
void blink_hr_field();
void display_set_time();


#endif