/* 
 * File:   rtc.c
 * Author: dell
 *
 * Created on September 21, 2024, 2:36 AM
 */

#include "rtc.h"

void rtc_update_time(uint8_t *rddata) {
    uint8_t data = 0x00;
    I2C1_Write(RTC_ADDRESS, data, 1);
    while (I2C1_IsBusy());
    I2C1_Read(RTC_ADDRESS, rddata, DATA_LENGTH);
    while (I2C1_IsBusy());
}



