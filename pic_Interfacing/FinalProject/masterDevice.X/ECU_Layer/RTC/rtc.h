/* 
 * File:   rtc.h
 * Author: dell
 *
 * Created on September 21, 2024, 2:36 AM
 */

#ifndef RTC_H
#define	RTC_H

#include "../../mcc_generated_files/system/system.h"

#define RTC_ADDRESS 0x68
#define DATA_LENGTH 7

#define SEC_IND     0
#define MIN_IND     1
#define HOUR_IND    2
#define RESERVED    3
#define DAY_IND     4
#define MONTH_IND   5
#define YEAR_IND    6

void rtc_update_time(uint8_t *rddata);

#endif	/* RTC_H */

