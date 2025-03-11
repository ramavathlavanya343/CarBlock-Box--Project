/*
 * File:   password.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:20 PM
 */


#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include <string.h>
#include "timer.h"
#include "main.h"
#include "eeprom.h"

/*Variables to keep track of password entry state*/
unsigned int flag1 = 0;
unsigned int i = 4;
unsigned int sec = 0;
unsigned int attempt = 3, pos = 5;
unsigned int delay = 0;
unsigned char original_password[5]="1010", user_password[5];
//unsigned char original_password[5], user_password[5];
unsigned char pass_addr = 100;
unsigned int j = 0;
extern char main_f;

/*Function to handle password entry and verification*/
void password(char key) {

    
    pass_addr = 100;
#if 1
    /*Load the original password from the EEPROM*/
    original_password[0] = read_external_eeprom(pass_addr);
    pass_addr++;
    original_password[1] = read_external_eeprom(pass_addr);
    pass_addr++;
    original_password[2] = read_external_eeprom(pass_addr);
    pass_addr++;
    original_password[3] = read_external_eeprom(pass_addr);
    pass_addr++;
    original_password[4] = read_external_eeprom(pass_addr);
//    original_password[4] = '\0';
#else  
    write_external_eeprom(pass_addr,'1');
    pass_addr++;
    write_external_eeprom(pass_addr,'0');
    pass_addr++;
    write_external_eeprom(pass_addr,'1');
    pass_addr++;
    write_external_eeprom(pass_addr,'0');
    pass_addr++;   
    write_external_eeprom(pass_addr,'\0');
#endif   
    pass_addr = 100;

    if (attempt != 0) {
        clcd_print("Enter password", LINE1(0));

        TMR0ON = 1;
        flag1 = 2;
        delay++;
        if (delay == 500) {
            clcd_putch('_', LINE2(5 + j));
        }
        if (delay == 1000) {
            delay = 0;
            clcd_putch(' ', LINE2(5 + j));
        }
        /*Handle key presses to enter the password*/
        if (i != 0) {
            if (key == MK_SW11) {
                clcd_putch('*', LINE2(pos));
                user_password[pos - 5] = '1';
                j++;
                pos++;
                i--;
                sec = 0; /* Reset the timer*/

            } else if (key == MK_SW12) {
                clcd_putch('*', LINE2(pos));
                user_password[pos - 5] = '0';
                j++;
                pos++;
                i--;
                sec = 0;
            }
        } else if (i == 0) {
            CLEAR_DISP_SCREEN;
            user_password[4] = '\0';
            /*compare it with the original password*/
            if (strcmp(original_password, user_password) == 0) 
            {
                clcd_print("Password Matched", LINE2(0));
                for (unsigned long int k = 10000; k--;);
                main_f = MENU;
                TMR0ON = 0;
                flag1 = 0;
                flag1 = 0;
                i = 4;
                j = 0;
                sec = 0;
                attempt = 3, pos = 5;
                delay = 0;
                CLEAR_DISP_SCREEN;

                return;
            } else {
                clcd_print("Wrong Password", LINE1(0));
                attempt--;
                clcd_print("Attempt left: ", LINE2(0));
                clcd_putch('0' + (attempt), LINE2(14));

                for (unsigned long int k = 500000; k--;);
                CLEAR_DISP_SCREEN;
                pos = 5;
                i = 4;
                j = 0;
                if (attempt == 0) {
                    sec = 120;
                }
            }
        }
    }
    
    /*Handle the blocking state after 3 incorrect attempts*/
    while (attempt == 0) {

        clcd_print("User Blocked", LINE1(0));
        clcd_print("Wait", LINE2(0));
        clcd_putch((sec / 100) % 10 + '0', LINE2(8));
        clcd_putch(((sec / 10) % 10) + '0', LINE2(9));
        clcd_putch(((sec) % 10) + '0', LINE2(10));

        for (delay = 500000; delay--;);
        flag1 = 1;
        TMR0ON = 1;

    }

}

