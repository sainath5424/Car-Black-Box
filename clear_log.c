/*
 * File:   clear_log.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:29 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
extern int ev_ind;
int clr_flag;
extern char main_f;
extern int i,back_i;
void clear_log(char key)
{
    //logic for clear
    clcd_print("CLEARING LOG  ",LINE1(0));
    if(clr_flag++==1000)
    {
        clr_flag=0;
        ev_ind=0;
        back_i = i;
        i = 10;
        store_event();
        i = back_i;
        CLEAR_DISP_SCREEN;
        main_f=DASHBOARD;
    }
}
