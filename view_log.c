
/*
 * File:   view_log.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:44 AM
 */


#include <xc.h>
#include "main.h"
#include "Ext_eeprom.h"
#include "matrix_keypad.h"
#include "clcd.h"
char view_arr[10][15];
int ext_ind;
int print_ind;
int ret_delay;
extern int ev_ind;
extern char main_f;
void view_log(char key) {
    //logic of view log
    for (int i = 0; i <= ev_ind; i++) {
        view_arr[i][0] = read_eeprom(i*10+0);
        view_arr[i][1] = read_eeprom(i*10+1);
        view_arr[i][2] = ':';
        view_arr[i][3] = read_eeprom(i*10+2);
        view_arr[i][4] = read_eeprom(i*10+3);
        view_arr[i][5] = ':';
        view_arr[i][6] = read_eeprom(i*10+4);
        view_arr[i][7] = read_eeprom(i*10+5);
        view_arr[i][8] = ' ';
       // view_arr[i][9] = ' ';
        view_arr[i][9] = read_eeprom(i*10+6);
        view_arr[i][10] = read_eeprom(i*10+7);
        view_arr[i][11] = ' ';
        //view_arr[i][13] = ' ';
        view_arr[i][12] = read_eeprom(i*10+8);
        view_arr[i][13] = read_eeprom(i*10+9);
    }
    
    clcd_print("# TIME     EV SP",LINE1(0));
    clcd_putch(print_ind+48,LINE2(0));
    clcd_print(view_arr[print_ind], LINE2(2));
    
    
        
    
   if (read_switches(LEVEL_CHANGE)==MK_SW12)
    {
        if (ret_delay++>=150)
        {
            ret_delay=0;
            CLEAR_DISP_SCREEN;
            main_f=MENU;
            print_ind=0;
            return;
        }
        
   }
   else if(ret_delay>0)
   {
       ret_delay=0;
       if (print_ind > 0 && ev_ind > 0) {
            print_ind--;
        }
   }
    if (key == MK_SW11) {
        if (print_ind<ev_ind-1) {
            print_ind++;
        }
    } 
}