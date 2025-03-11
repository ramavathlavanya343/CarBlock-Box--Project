/*
 * File:   isr.c
 * Author: Reliance
 *
 * Created on 13 August, 2024, 12:28 PM
 */

#include <xc.h>
#include "timer.h"
#include "main.h"
#include "clcd.h"

extern unsigned int i, sec, attempt, pos, flag1;
extern char main_f;

void __interrupt() isr(void) {
    static unsigned short count;


    if (TMR0IF) {
        TMR0 = TMR0 + 8;

        if (++count == 20000) {
            count = 0;
            if (flag1 == 1) {
                sec--;
                if (sec == 0) {
                    CLEAR_DISP_SCREEN;
                    attempt = 3;
                    pos = 5;
                    i = 0;
                    main_f = DASHBOARD;
                }
            }

            if (flag1 == 2) {

                sec++;
                if (sec == 5) {
                    CLEAR_DISP_SCREEN;
                    attempt = 3;
                    pos = 5;
                    i = 0;
                    main_f = DASHBOARD;
                    TMR0IF = 0;
                }
            }

        }
    }
    TMR0IF = 0;
}

