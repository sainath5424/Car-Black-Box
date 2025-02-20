/*
 * File:   password.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:42 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"
unsigned char pass[4]={1,1,1,1};
unsigned char e_pass[4];
int ind=0,atmp_delay=0;
unsigned char pass_flag=0;
int attempts=2;
unsigned int wait;
extern char main_f;
extern int wait1=120;
char f1=0;
int cur_delay;
char str_fl;
extern unsigned char str_flag;
void password(char key)
{
    //password logic
    if(ind<4)
    {
        clcd_print("ENTER PASSWORD",LINE1(0));
        //clcd_putch(wait+48,LINE2(0));
        if(cur_delay++==250)
        {
            clcd_putch('_',LINE2(ind));
        }
        else if(cur_delay==500)
        {
            clcd_putch(' ',LINE2(ind));
            cur_delay=0;
        }
        if(key==MK_SW11)
        {
            e_pass[ind]=1;
            clcd_putch('*',LINE2(ind));
            ind++;
            wait=0;
        }
        else if(key==MK_SW12)
        {
            e_pass[ind]=0;
            clcd_putch('*',LINE2(ind));
            ind++;
            wait=0;
        }
        if(key==ALL_RELEASED && wait==5)
        {
            main_f=DASHBOARD;
            wait=0;
            TMR0ON=0;
        }
     if(ind == 4)
         wait1=120;
    }
    if(ind==4)
    {
        for(int j=0;j<4;j++)
        {
            if(e_pass[j]!=pass [j])
            {
                pass_flag=1;
                break;
            }
        }
        if(pass_flag)
        {
            if(attempts==0)
            {   TMR0ON=1;
            TMR0IE = 1;
                clcd_print("YOU ARE BLOCKED",LINE1(0));
                clcd_print("WAIT FOR SEC",LINE2(0));
                clcd_putch((wait1/100)+48,LINE2(9));
                clcd_putch(((wait1/10%10))+48,LINE2(10));
                clcd_putch((wait1%10)+48,LINE2(11));
                if(wait1==0)
                    {
                    TMR0ON = 1;
                    TMR0IE = 1;
                        ind=0;
                        attempts=2;
                        pass_flag=0;
                        wait1=120;
                        wait=0;
                        CLEAR_DISP_SCREEN;
                    }
            }
            
            else
            {
                clcd_print("TRY AGAIN       ",LINE1(0));
                clcd_putch(attempts+48,LINE2(0));
                clcd_print(" attempts left",LINE2(1)); 
                if(atmp_delay++==1000)
                {
                    atmp_delay=0;
                    if(attempts>0)
                    {
                        ind=0;
                        attempts--;
                        pass_flag=0;
                        CLEAR_DISP_SCREEN;
                    }
                }
            }
        }
        else
        {
            //clcd_print("SUCCESSFULL   ",LINE2(0));
            TMR0ON = 0;
            main_f = MENU;
            str_flag=0;
            str_fl=1;
            CLEAR_DISP_SCREEN;
            ind=0;
        }
    }
   
}