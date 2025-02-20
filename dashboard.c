/*
 * File:   dashboard.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:34 AM
 */


#include <xc.h>
#include "main.h"
#include"adc.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include "timer0.h"


extern char arr[][3];
extern unsigned char time[9];
extern unsigned char speed = 0;
extern int i;
extern char main_f = 0,key;
void dashboard() {

    //display logic
    clcd_print("TIME     EV   SP", LINE1(0));
    clcd_print(time, LINE2(0));
    clcd_print(arr[i], LINE2(9));
    clcd_print(arr[i], LINE2(9));
    clcd_putch(speed / 10 + '0', LINE2(14));
    clcd_putch(speed % 10 + '0', LINE2(15));
    
    if(key==MK_SW11)
    {
        main_f=PASSWORD;
        CLEAR_DISP_SCREEN;
        TMR0ON=1;
        TMR0IE=1;
                
    }
}

