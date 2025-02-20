/*
 * File:   download_log.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:35 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "uart.h"
#include "Ext_eeprom.h"
int dow_delay;
extern char view_arr[10][15];
extern int ev_ind;
extern char main_f;
void download_log()
{
    //download log logic
    clcd_print("DOWNLOADING  ",LINE1(0));
    for (int i = 0; i < ev_ind; i++) {
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
    
    if(dow_delay++==250)
    {
        dow_delay=0;
        main_f=DASHBOARD;
        CLEAR_DISP_SCREEN;
        puts("#TIME     EV  SP");
        for (int i = 0; i < ev_ind; i++) {
            puts("\n\r");
            puts(view_arr[i]);

        }
    }
}
