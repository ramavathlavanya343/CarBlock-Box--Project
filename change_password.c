/*
 * File:   change_password.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:15 PM
 */

#include <xc.h>
#include "clcd.h"
#include "matrix_keypad.h"
#include <string.h>
#include "timer.h"
#include "main.h"

/*External variables used in the password change process*/
extern unsigned int i;
extern unsigned int sec;
extern unsigned int attempt;
extern unsigned int pos;
extern unsigned int delay;
extern unsigned char original_password[5];
extern unsigned char user_password[];
unsigned old_pass[5];
unsigned char new_pass[5];
unsigned char reset_pass[5];
extern unsigned int j;
extern char main_f;
unsigned char pass_flag  = 0;
unsigned char pass_addr = 100;
unsigned char k;

/*Function to handle the password change process*/
void change_pass(char key)
{

    /*Load the original password from EEPROM if not already done*/
    if (pos == 5) 
    {
        pass_addr = 100;
        while (k < 4) 
        {
            original_password[k] = read_external_eeprom(pass_addr);
            pass_addr++;
            k++;
        }
        original_password[k] = '\0';
    }
   
    if (pass_flag == 0) 
    {

        clcd_print("Enter old password", LINE1(0));

        delay++;
        if (delay == 500) {
            clcd_putch('_', LINE2(5 + j));
        }
        if (delay == 1000) {
            delay = 0;
            clcd_putch(' ', LINE2(5 + j));
        }
        if (i != 0)
        {
            if (key == MK_SW11) 
            {
                clcd_putch('*', LINE2(pos));
                user_password[pos - 5] = '1';
                j++;
                pos++;
                i--;


            } 
            else if (key == MK_SW12)
            {
                clcd_putch('*', LINE2(pos));
                user_password[pos - 5] = '0';
                j++;
                pos++;
                i--;

            }
        } 
        else if (i == 0)
        {
            CLEAR_DISP_SCREEN;
            user_password[4] = '\0';
            original_password[4] = '\0';
            
            /*Check if the entered password matches the original password*/
            if (strcmp(user_password, original_password) == 0)
            {
                pass_flag = 1;
                pos = 5;
                j = 0;
                i = 4;
            } 
            else
            {
                clcd_print("Password Not Matched", LINE2(0));

                pass_flag = 0;
                pos = 5;
                j = 0;
                i = 4;
                attempt = 3;
                CLEAR_DISP_SCREEN;
                main_f = MENU;
                return;
            }
        }
    } 
    else if (pass_flag == 1)
    {
        clcd_print("Enter New password", LINE1(0));
        
        delay++;
        if (delay == 500) {
            clcd_putch('_', LINE2(5 + j));
        }
        if (delay == 1000) {
            delay = 0;
            clcd_putch(' ', LINE2(5 + j));
        }
        
        
        if (i != 0) 
        {
            if (key == MK_SW11) {
                clcd_putch('*', LINE2(pos));
                new_pass[pos - 5] = '1';
                j++;
                pos++;
                i--;


            } else if (key == MK_SW12) {
                clcd_putch('*', LINE2(pos));
                new_pass[pos - 5] = '0';
                j++;
                pos++;
                i--;

            }
        } 
        else if (i == 0)
        {
            CLEAR_DISP_SCREEN;
            new_pass[5] = '\0';
            pass_flag = 2;
            pos = 5;
            attempt = 3;
            j = 0;
            i = 4;
        }
    }
    else if (pass_flag == 2) 
    {
        clcd_print("Re-Enter New pass", LINE1(0));
        
        /*Handle blinking cursor for password entry*/
        delay++;
        if (delay == 500) {
            clcd_putch('_', LINE2(5 + j));
        }
        if (delay == 1000) {
            delay = 0;
            clcd_putch(' ', LINE2(5 + j));
        }
        
        if (i != 0)
        {
            if (key == MK_SW11) {
                clcd_putch('*', LINE2(pos));
                reset_pass[pos - 5] = '1';

                j++;
                pos++;
                i--;


            } else if (key == MK_SW12) {
                clcd_putch('*', LINE2(pos));
                reset_pass[pos - 5] = '0';
                j++;
                pos++;
                i--;

            }
        } 
        else if (i == 0) 
        {
            CLEAR_DISP_SCREEN;
            reset_pass[5] = '\0';
            new_pass[5] = '\0';
            attempt = 3;
            i=4,j=0,pos = 5;

            /*Check if the re-entered password matches the new password*/
            if (strcmp(new_pass, reset_pass) == 0) 
            {
                pass_addr = 100;
                clcd_print("Password Changed", LINE2(0));
                CLEAR_DISP_SCREEN;
                
                /*Store the new password in EEPROM*/
                pass_addr = 100;
                for (char k = 0; k < 4; k++) 
                {
                    write_external_eeprom(pass_addr, new_pass[k]);
                    pass_addr++;
                }
                pass_addr = 100;
                for (unsigned long int k = 500000; k--;);               

                pass_flag = 0;
                attempt = 3;
                CLEAR_DISP_SCREEN;
                main_f = MENU;
            } 
            else 
            {
                clcd_print("Password Not Matched", LINE2(0));
                pass_flag = 0;
                pos = 5;
                j = 0;
                i = 4;
                attempt = 3;
                main_f = MENU;
            }
        }
    }
}

