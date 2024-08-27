/* 
 * File:   eeprom.c
 * Author: Salah-Eldin
 *
 * Created on August 28, 2024
 */

//==================================================
// Includes
//==================================================
#include "eeprom.h"

//==================================================
// Functions Definitions
//==================================================

/**
 * @brief Writes one byte of data to a specific EEPROM Address.
 * 
 * @param bAdd The EEPROM address to write at.
 * @param bData Data to be written.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType EEPROM_WriteByte(uint16 bAdd, uint8 bData) {
    Std_ReturnType ret = E_OK;

    //Reads the Interrupt Status "enabled or disabled"
    uint8 Global_Interrupt_Status = INTCONbits.GIE;

    //Updates the Data Memory Address to write at
    EEADRH = (uint8) ((bAdd >> 8) & 0x03);
    EEADR = (uint8) (bAdd & 0xFF);

    //Data Memory Value to write
    EEDATA = bData;

    //Access EEPROM
    EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;

    //Allows write cycles to Flash program/data EEPROM
    EECON1bits.WREN = ALLOW_WRITE_CYCLES;

    //Disable all interrupts
    INTCONbits.GIE = INTERRUPT_DISABLE;

    //Write the required seq 
    EECON2 = 0x55;
    EECON2 = 0xAA;

    //Initiates a data EEPROM erase/write cycle
    EECON1bits.WR = INITIATE_EEPROM_DATA_WRITE_ERASE;

    //Wait for a while unitl write is completed
    while (INITIATE_EEPROM_DATA_WRITE_ERASE == EECON1bits.WR);

    //Inhibits write cycles to Flash program/data EEPROM
    EECON1bits.WREN = INHIBITS_WRITE_CYCLES;

    //Restores the Interrupt Status "enabled or disabled"
    INTCONbits.GIE = Global_Interrupt_Status;

    return ret;
}

/**
 * @brief Reads one byte of data from a specific EEPROM Address.
 * 
 * @param bAdd The EEPROM address to read from..
 * @param bData A pointer to store the read data.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType EEPROM_ReadByte(uint16 bAdd, uint8 *bData) {
    Std_ReturnType ret = E_OK;

    if (NULL == bData) {
        ret = E_NOT_OK;
    } else {
        //Updates the Data Memory Address to read
        EEADRH = (uint8) ((bAdd >> 8) & 0x03);
        EEADR = (uint8) (bAdd & 0xFF);
        //Access EEPROM
        EECON1bits.EEPGD = ACCESS_EEPROM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        //Initiates an EEPROM read
        EECON1bits.RD = INITIATE_EEPROM_DATA_READ;
        NOP();
        NOP();
        //Reads data
        *bData = EEDATA;
    }
    return ret;
}