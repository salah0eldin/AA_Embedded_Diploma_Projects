/* 
 * File:   interrupt_gen_config.h
 * Author: Salah-Eldin
 *
 * Created on August 24, 2024
 */

#ifndef INTERRUPT_GEN_CONFIG_H
#define	INTERRUPT_GEN_CONFIG_H

//==================================================
//                  Includes
//==================================================

//==================================================
//                  Macro Declarations
//==================================================
#define INTERRUPT_FEATURE_ENABLE                  1U

//#define INTERRUPT_PRIORITY_LEVELS_ENABLE          INTERRUPT_FEATURE_ENABLE   

#define EXTERNAL_INTERRUPT_INTx_ENABLE            INTERRUPT_FEATURE_ENABLE  
#define EXTERNAL_INTERRUPT_ONCHANGE_ENABLE        INTERRUPT_FEATURE_ENABLE 

//#define ADC_INTERRUPT_ENABLE_FEATURE              INTERRUPT_FEATURE_ENABLE

#define TIMER0_INTERRUPT_ENABLE_FEATURE           INTERRUPT_FEATURE_ENABLE
#define TIMER1_INTERRUPT_ENABLE_FEATURE           INTERRUPT_FEATURE_ENABLE
#define TIMER2_INTERRUPT_ENABLE_FEATURE           INTERRUPT_FEATURE_ENABLE
#define TIMER3_INTERRUPT_ENABLE_FEATURE           INTERRUPT_FEATURE_ENABLE

#define CCP1_INTERRUPT_ENABLE_FEATURE             INTERRUPT_FEATURE_ENABLE
#define CCP2_INTERRUPT_ENABLE_FEATURE             INTERRUPT_FEATURE_ENABLE

#define SPI_INTERRUPT_ENABLE_FEATURE              INTERRUPT_FEATURE_ENABLE
#define I2C_INTERRUPT_ENABLE_FEATURE              INTERRUPT_FEATURE_ENABLE

//==================================================
//                 Macro Functions Declarations 
//==================================================

//==================================================
//                  Data Types Declarations
//==================================================

//==================================================
//                  Functions Declarations
//==================================================

#endif	/* INTERRUPT_GEN_CONFIG_H */

