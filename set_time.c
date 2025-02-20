/*
 * File:   set_time.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:43 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "ds1307.h"
int bl_i=7;
int hrs,min,sec;
extern char st_flag;
int blink_delay,st_delay,back_delay;
extern char main_f;
extern int i,back_i;
extern unsigned char time[9];
void settime(char key)
{
    //logic for set time
    if(st_flag)
    {
       hrs=(((time[0] - 48) * 10) + (time[1] - 48));
       min=(((time[3] - 48) * 10) + (time[4] - 48));
       sec=(((time[6] - 48) * 10) + (time[7] - 48));
       st_flag = 0;
    }
    clcd_print("    SET TIME     ",LINE1(0));
    if (blink_delay++<250)
    {
        clcd_putch('_',LINE2(bl_i));
        clcd_putch('_',LINE2(bl_i-1));
    }
    else if(blink_delay<500)
    {
        clcd_putch(hrs / 10 + '0', LINE2(0));
        clcd_putch(hrs % 10 + '0', LINE2(1));
        clcd_putch(':', LINE2(2));
        clcd_putch(min / 10 + '0', LINE2(3));
        clcd_putch(min % 10 + '0', LINE2(4));
        clcd_putch(':', LINE2(5));
        clcd_putch(sec / 10 + '0', LINE2(6));
        clcd_putch(sec % 10 + '0', LINE2(7));
    }
    else
    {
        blink_delay=0;
    }
    if(read_switches(LEVEL_CHANGE)==MK_SW12)
    {
        if(back_delay++>=200)
        {
            back_delay=0;
            main_f=DASHBOARD;
            return;
        }
    }
    else if(back_delay>0)
    {
        back_delay=0;
        bl_i=bl_i-3;
        if(bl_i<0)
        {
            bl_i=7;
        }
    }
    if(read_switches(LEVEL_CHANGE)==MK_SW11)
    {
        if(st_delay++>=500)
        {
            st_delay=0;
            write_ds1307(SEC_ADDR,(sec/10<<4)|(sec%10&0x0f));
            write_ds1307(MIN_ADDR,(min/10<<4)|(min%10&0x0f));
            write_ds1307(HOUR_ADDR,(hrs/10<<4)|(hrs%10&0x0f));
            back_i = i;
            i = 11;
            store_event();
            i = back_i;
            main_f=DASHBOARD;
            
        }
        
    }
    else if(st_delay>0)
    {
        st_delay=0;
        if(bl_i==7 )
        {
            if(sec<59)
            {
                sec++;
            }
            else
            {
                sec=0;
            }
        }
        else if(bl_i==4)
        {
            if(min<59)
            {
                min++;
            }
            else
            {
                min=0;
            }
        }
        else if(bl_i==1)
        {
            if(hrs<23)
            {
                hrs++;
            }
            else
            {
                hrs=0;
            }
        }
    }
}