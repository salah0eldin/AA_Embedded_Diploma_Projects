/* 
 * File:   disp.h
 * Author: dell
 *
 * Created on September 21, 2024, 3:01 AM
 */

#ifndef DISP_H
#define	DISP_H

#include "../../mcc_generated_files/system/system.h"
#include "../RTC/rtc.h"

void disp_display_uart_ascii(uint8_t *data);

void disp_display_uart_time_date(uint8_t *data);

#endif	/* DISP_H */

