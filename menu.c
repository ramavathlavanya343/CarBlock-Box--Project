/*
 * File:   menu.c
 * Author: Reliance
 *
 * Created on 9 August, 2024, 2:20 PM
 */


#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"

/*Array of menu items to be displayed*/
char *menu_items[] = {"View log      ", "Download      ", "Clear Log     ", "Set time      ", "Change pass   "};
unsigned int flag2 = 0;
unsigned int current_item = 0;
extern char main_f, menu_f;

/*Function to display the menu on the CLCD*/
void display_menu()
{
    /*Display the currently highlighted menu item on the first line*/
    clcd_print(menu_items[current_item], LINE1(2));
    /*Display the next menu item on the second line*/
    clcd_print(menu_items[current_item + 1], LINE2(2));

   /*Display the cursor ('*') on the correct line based on flag2*/
    if (flag2 == 0) {
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));

    } else {
        clcd_putch('*', LINE2(0));
        clcd_putch(' ', LINE1(0));

    }
}

/*Function to handle menu navigation and selection based on the key pressed*/
void menu(char key) {
    display_menu();
    
    /*Handle key press for scrolling through the menu and selecting items*/
    if (key == MK_SW11) { // Scroll down'=
        if (flag2 == 1) {
            flag2 = 0;
        } else if (current_item > 0) {
            current_item--;
            
        }
    } else if (key == MK_SW12) { // Scroll up
        if (flag2 == 0) flag2 = 1;
        else if (current_item < 3) {
            current_item++;
            
        }
    } else if (key == MK_LONG_SW12) { //long press
        CLEAR_DISP_SCREEN;
        main_f = DASHBOARD;
        current_item = 0;
        flag2 = 0;
        return;
    } else if (key == MK_LONG_SW11) {  //long press
        CLEAR_DISP_SCREEN;
        main_f = MENU_ENTER;
        menu_f = current_item + flag2;
        TMR0ON = 0;
        for(unsigned long int k = 500000;k--;);
        current_item = 0;
        flag2 = 0;
        return;
    }
}


