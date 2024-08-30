/* 
 * File:   interrupt_manager.h
 * Author: Salah-Eldin
 *
 * Created on August 24, 2024
 */

#ifndef INTERRUPT_MANAGER_H
#define	INTERRUPT_MANAGER_H

//==================================================
// Includes
//==================================================
#include "interrupt_config.h"

//==================================================
// Macro Declarations
//==================================================

//==================================================
// Macro Functions Declarations 
//==================================================

//==================================================
// Data Types Declarations
//==================================================

//==================================================
// Functions Declarations
//==================================================
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB_src);
void RB5_ISR(uint8 RB_src);
void RB6_ISR(uint8 RB_src);
void RB7_ISR(uint8 RB_src);

//void ADC_ISR(void);

void TIMR0_ISR(void);
void TIMR1_ISR(void);
void TIMR2_ISR(void);
void TIMR3_ISR(void);

//void CCP1_ISR(void);
//void CCP2_ISR(void);

//void EUSART_TX_ISR(void);
//void EUSART_RX_ISR(void);

//void SPI_ISR(void);
//void I2C_ISR(void);
//void I2C_BUS_COL_ISR(void);

#endif	/* INTERRUPT_MANAGER_H */

