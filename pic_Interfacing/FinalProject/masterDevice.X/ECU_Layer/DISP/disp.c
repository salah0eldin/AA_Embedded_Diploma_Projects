/* 
 * File:   disp.c
 * Author: dell
 *
 * Created on September 21, 2024, 3:02 AM
 */

#include "disp.h"

void disp_display_uart_ascii(uint8_t *data){
    while(*data){
        EUSART_Write(*data);
        while(!EUSART_IsTxDone());
        data++;
    }
}

void disp_display_uart_time_date(uint8_t *data){
    disp_display_uart_ascii("Date : ");
    uint8_t dispData[9] = {0};
    dispData[0] = (data[YEAR_IND] >> 4) + '0';
    dispData[1] = (data[YEAR_IND] & 0x0F) + '0';
    dispData[2] = '-';
    dispData[3] = (data[MONTH_IND] >> 4) + '0';
    dispData[4] = (data[MONTH_IND] & 0x0F) + '0';
    dispData[5] = '-';
    dispData[6] = (data[DAY_IND] >> 4) + '0';
    dispData[7] = (data[DAY_IND] & 0x0F) + '0';
                        
    disp_display_uart_ascii(dispData);
    
    disp_display_uart_ascii(" <> Time : ");
    dispData[0] = (data[HOUR_IND] >> 4) + '0';
    dispData[1] = (data[HOUR_IND] & 0x0F) + '0';
    dispData[2] = ':';
    dispData[3] = (data[MIN_IND] >> 4) + '0';
    dispData[4] = (data[MIN_IND] & 0x0F) + '0';
    dispData[5] = ':';
    dispData[6] = (data[SEC_IND] >> 4) + '0';
    dispData[7] = (data[SEC_IND] & 0x0F) + '0';
                        
    disp_display_uart_ascii(dispData);
    
    EUSART_Write('\r');
}


