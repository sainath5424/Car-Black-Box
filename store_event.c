/*
 * File:   store_event.c
 * Author: AANIL
 *
 * Created on 25 September, 2024, 8:44 AM
 */


#include <xc.h>
#include "main.h"
#include "Ext_eeprom.h"
#include "clcd.h"

unsigned char event[10];
extern unsigned char time[9];
extern char arr[][3];
extern unsigned char speed;
extern int i;
extern char view_arr[10][15];
char dummy[11];
int ev_ind,data_ind;
char data;
void store_event()
{
    //storing the event in event array
    event[0]=time[0];
    event[1]=time[1];
    event[2]=time[3];
    event[3]=time[4];
    event[4]=time[6];
    event[5]=time[7];
    event[6]=arr[i][0];
    event[7]=arr[i][1];
    event[8]=speed/10+48;
    event[9]=speed%10+48;
    //checking that index of event array for doing swap
    if(ev_ind==10)
    {  
        //logic for swap the data to previous 
        for(int i=1;i<10;i++)
        {
            for(int j=0;j<10;j++)
            {
                data=read_eeprom(i*10+j);
                write_eeprom((i-1)*10+j,data);
            }
        }
        ev_ind--;
        
    }
    //writing data to eeprom
    for(int i=0;i<10;i++)
        {
            write_eeprom(ev_ind*10+i,event[i]);
        }
        ev_ind++;
    
}