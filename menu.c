/*
 * File:   menu.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:41 AM
 */


#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
unsigned char menu_arr[5][17]={"DISPLAY LOG     ","DOWNLOAD LOG     ","CLEAR LOG       ","SET TIME        ","CHANGE PASSWORD  "};
int menu_ind;
unsigned char str_flag;
extern int i,back_i;
unsigned char menu_flag;
int ret_delay,ret_delay1;
char st_flag;
extern char str_fl;
extern char main_f,menu_f;
void menu(char key)
{
    //logic for menu
    if(read_switches(LEVEL_CHANGE)==MK_SW12)
    {
        if(ret_delay++>200)
        {
            ret_delay=0;
            CLEAR_DISP_SCREEN;
            main_f=DASHBOARD;
            menu_ind=0;
            str_flag=0;
            return;
        }
    }
    else if(ret_delay>0)
    {
        ret_delay=0;
        if(str_flag==0 && menu_ind>0)
        {
            menu_ind--;
        }
        str_flag=0;
    }
    
    
    if(read_switches(LEVEL_CHANGE)==MK_SW11)
    {
        if(ret_delay1++>200)
        {
            ret_delay1=0;
            if(str_flag+menu_ind==VIEWLOG)
            {
                CLEAR_DISP_SCREEN;
                main_f=MENU_ENTER;
                menu_f=VIEWLOG;
                menu_ind=0;
                str_flag=0;
                return;
            }
            else if(str_flag+menu_ind==DOWNLOADLOG)
            {
                CLEAR_DISP_SCREEN;
                main_f=MENU_ENTER;
                menu_f=DOWNLOADLOG;
                back_i=i;
                i=9;
                store_event();
                i=back_i;
                menu_ind=0;
                str_flag=0;
                return;
            }
            else if(str_flag+menu_ind==CLEARLOG)
            {
                CLEAR_DISP_SCREEN;
                main_f=MENU_ENTER;
                menu_f=CLEARLOG;
                menu_ind=0;
                return;
            }
            else if(str_flag+menu_ind==SETTIME)
            {
                CLEAR_DISP_SCREEN;
                main_f=MENU_ENTER;
                menu_f=SETTIME;
                st_flag=1;
                menu_ind=0;
                str_flag=0;
                return;
            }
            else if(str_flag+menu_ind==CHANGEPASS)
            {
                CLEAR_DISP_SCREEN;
                main_f=MENU_ENTER;
                menu_f=CHANGEPASS;
                back_i=i;
                i=12;
                store_event();
                i=back_i;
                menu_ind=0;
                str_flag=0;
                return;
            }
            
        }
    }
    else if (ret_delay1 > 0) {
        ret_delay1 = 0;
        if (str_flag == 1 && menu_ind < 3) {
            menu_ind++;
        }
        str_flag = 1;
    }
    if (str_flag)
    {
        clcd_putch(' ',LINE1(0));
        clcd_putch('*',LINE2(0));
    }
    else
    {
        clcd_putch('*',LINE1(0));
        clcd_putch(' ',LINE2(0));
    }
    clcd_print(menu_arr[menu_ind],LINE1(1));
    clcd_print(menu_arr[menu_ind+1],LINE2(1));
    if(str_fl)
    {
        str_fl=0;
        str_flag=0;
    }

}