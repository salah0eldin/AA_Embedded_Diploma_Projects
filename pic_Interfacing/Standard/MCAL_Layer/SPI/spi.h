/* 
 * File:   spi.h
 * Author: Salah-Eldin
 *
 * Created on September 5, 2024
 */

#ifndef SPI_H
#define	SPI_H

//==================================================
// Includes
//==================================================
#include "spi_cfg.h"
#include "../GPIO/gpio.h"
#include "../interrupt/internal_interrupt.h"

//==================================================
// Macro Declarations
//==================================================
/* Master Synchronous Serial Port Mode Select */
#define SPI_MASTER_FOSC_DIV4   0 /* SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin */
#define SPI_MASTER_FOSC_DIV16  1 /* SPI Slave mode, clock = SCK pin, SS pin control enabled */
#define SPI_MASTER_FOSC_DIV64  2 /* SPI Master mode, clock = TMR2 output/2 */
#define SPI_MASTER_FOSC_TMR2   3 /* SPI Master mode, clock = FOSC/64 */
#define SPI_SLAVE_SS_ENABLE    4 /* SPI Master mode, clock = FOSC/16 */
#define SPI_SLAVE_SS_DISABLE   5 /* SPI Master mode, clock = FOSC/4 */

/* Clock Polarity Select */
#define SPI_IDLE_STATE_HIGH_LEVEL   1 /* Idle state for clock is a high level */
#define SPI_IDLE_STATE_LOW_LEVEL    0 /* Idle state for clock is a low level */

/* SPI Sample Select */
#define SPI_DATA_SAMPLE_MIDDLE      0 /* Input data sampled at middle of data output time */
#define SPI_DATA_SAMPLE_END         1 /* Input data sampled at end of data output time */

/* SPI Clock Select */
#define SPI_TRANSMIT_ACTIVE_TO_IDLE 1 /* Transmit occurs on transition from active to Idle clock state */
#define SPI_TRANSMIT_IDLE_TO_ACTIVE 0 /* Transmit occurs on transition from Idle to active clock state */

/* Receive Overflow Indicator */
#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECTED      1
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECTED  0

/* Write Collision Detect */
#define SPI_WRITE_COLLISION_DETECTED             1
#define SPI_WRITE_COLLISION_NOT_DETECTED         0

/* Buffer Full Status bit (Receive mode only) */ 
#define SPI_BUFFER_FULL_RECEIVE_COMPLETE         1
#define SPI_BUFFER_FULL_RECEIVE_NOT_COMPLETE     0

//==================================================
// Macro Functions Declarations 
//==================================================
/* Master Synchronous Serial Port Enable */
#define SPI_ENABLE_MODULE()    (SSPCON1bits.SSPEN = 1) /* Enables serial port and configures SCK, SDO, SDI and SS as serial port pins */
#define SPI_DISABLE_MODULE()   (SSPCON1bits.SSPEN = 0) /*  Disables serial port and configures these pins as I/O port pins */
                                  
//==================================================
// Data Types Declarations
//==================================================

typedef struct{
    uint8 ClockPolarity : 2; /* Clock Polarity Select */
    uint8 SampleSelect : 2;  /* SPI Sample Select */
    uint8 ClockSelect : 2;   /* SPI Clock Select */
    uint8 Reserved : 2;
}SPI_Control_Config;

typedef struct{
#if SPI_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
    void (* MSSP_SPI_InterruptHandler)(void);
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
    interrupt_priority priority;
#endif
#endif
    uint8 spi_mode;
    SPI_Control_Config spi_config;
}SPI_Config;

//==================================================
// Functions Declarations
//==================================================
/**
 * @brief Initializes the SPI module based on the provided configuration.
 * 
 * This function configures the SPI module according to the specified configuration settings, 
 * enabling the appropriate pins and setting the communication parameters such as clock polarity, phase, 
 * and data order.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the initialization.
 */
Std_ReturnType SPI_Init(const SPI_Config *Config);

/**
 * @brief De-Initializes the SPI module.
 * 
 * This function disables the SPI module and releases any resources used.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during de-initialization.
 */
Std_ReturnType SPI_DeInit(const SPI_Config *Config);

/**
 * @brief Sends a single byte of data via SPI.
 * 
 * This function transmits one byte of data using the SPI module as per the provided configuration.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data The byte of data to be transmitted.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during transmission.
 */
Std_ReturnType SPI_Master_Send_Receive_Byte(const SPI_Config *Config, const uint8 _dataT, uint8 *_dataR);

/**
 * @brief Receives a single byte of data via SPI.
 * 
 * This function reads one byte of data from the SPI module into the provided data pointer.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data A pointer to store the received byte.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during reception.
 */
Std_ReturnType SPI_Slave_Send_Receive_Byte(const SPI_Config *Config, const uint8 _dataT, uint8 *_data);

/**
 * @brief Sends a single byte of data via SPI in a non-blocking manner.
 * 
 * This function transmits one byte of data asynchronously, allowing the CPU to perform other tasks while the 
 * SPI transmission completes.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data The byte of data to be transmitted.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during transmission.
 */
Std_ReturnType SPI_Send_Byte_NonBlocking(const SPI_Config *Config, const uint8 _data);

/**
 * @brief Receives a single byte of data via SPI in a non-blocking manner.
 * 
 * This function reads one byte of data asynchronously from the SPI module into the provided data pointer.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data A pointer to store the received byte.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during reception.
 */
Std_ReturnType SPI_Read_Byte_NonBlocking(const SPI_Config *Config, uint8 *_data);

#endif	/* SPI_H */

