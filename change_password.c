/*
 * File:   change_password.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:26 AM
 */


#include <xc.h>
#include "main.h"
#include"clcd.h"
#include "matrix_keypad.h"
#include "Ext_eeprom.h"
extern unsigned char pass[4];
extern unsigned char e_pass[4];
extern int cur_delay,ind=0;
char cmp_flag;
unsigned char ch_pass[4];
int ch_ind;
char main_f;
void change_pass(char key)
{
    //change password logic
    //checking entering password index is less than 4
    if(ind<4)
    {
        clcd_print("ENTER PASSWORD",LINE1(0));
        //logic for blinking cursor at char entering position
        if(cur_delay++==250)
        {
            clcd_putch('_',LINE2(ind));
        }
        else if(cur_delay==500)
        {
            clcd_putch(' ',LINE2(ind));
            cur_delay=0;
        }
        //logic for writing the password to array by using switches
        if(key==MK_SW11)
        {
            e_pass[ind]=1;
            clcd_putch('*',LINE2(ind));
            ind++;
        }
        else if(key==MK_SW12)
        {
            e_pass[ind]=0;
            clcd_putch('*',LINE2(ind));
            ind++;
        }
        //checking the condition for getting password from eeprom 
        if(ind==4)
        {
            for (int i = 0; i < 4; i++) {
                pass[i] = read_eeprom(0xc8 + i);
            }
            cur_delay=0;
            CLEAR_DISP_SCREEN;
        }
    }
    //checking the index for comparing the password which we entered with password from eeprom
    else if(ind==4)
    {
        //logic for comparing passwords
        for(int i=0;i<4;i++)
        {
            if(pass[i]!=e_pass[i])
            {
                cmp_flag=1;
            }
        }
        //checking the password is matched or not by using flag variable 
        if(!cmp_flag)
        {
            //if password is matched then checking the new password array index is less than 4 or not to enter new password
            if(ch_ind<4)
            {
                clcd_print("ENTER NEWPASS     ", LINE1(0));
                //logic for blinking cursor
                if (cur_delay++ == 250) {
                    clcd_putch('_', LINE2(ch_ind));
                } else if (cur_delay == 500) {
                    clcd_putch(' ', LINE2(ch_ind));
                    cur_delay = 0;
                }
                //logic for writing the new password to new password array
                if (key == MK_SW11) {
                    ch_pass[ch_ind] = 1;
                    clcd_putch('*',LINE2(ch_ind));
                    ch_ind++;
                } else if (key == MK_SW12) {
                    ch_pass[ch_ind] = 0;
                    clcd_putch('*',LINE2(ch_ind));
                    ch_ind++;
                    
                }
                if(ch_ind==4)
                {
                    cur_delay=0;
                    CLEAR_DISP_SCREEN;
                }
            }
            //checking that new password is entered or not
            if(ch_ind==4)
            {
                clcd_print("PASSWORD CHANGED",LINE1(0));
                if (cur_delay++ == 2000) {
                    ind=0;
                    ch_ind=0;
                    for (int i = 0; i < 4; i++) {
                        //writing new password to eeprom
                        write_eeprom(0xc8 + i, ch_pass[i]);
                        //again reading password from eeprom and storing into pass array to compare the entering password while entering into menu
                        pass[i] = read_eeprom(0xc8 + i);
                    }
                    CLEAR_DISP_SCREEN;
                    main_f = MENU;
                    return;
                }
            }
        }
        //else part for entered password is matched or not with original password
        else
        {
            clcd_print("WRONG PASSWORD   ",LINE1(0));
            if(cur_delay++==2000)
            {
                CLEAR_DISP_SCREEN;
                main_f=MENU;
                return;
            }
            
        }
    }
}