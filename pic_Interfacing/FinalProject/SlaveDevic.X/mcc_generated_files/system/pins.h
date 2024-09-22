/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.1.1
*/

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RC0 aliases
#define Alarm_TRIS                 TRISCbits.TRISC0
#define Alarm_LAT                  LATCbits.LATC0
#define Alarm_PORT                 PORTCbits.RC0
#define Alarm_WPU                  WPUCbits.
#define Alarm_OD                   ODCONCbits.
#define Alarm_ANS                  ANSELCbits.
#define Alarm_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define Alarm_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define Alarm_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define Alarm_GetValue()           PORTCbits.RC0
#define Alarm_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define Alarm_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define Alarm_SetPullup()          do { WPUCbits. = 1; } while(0)
#define Alarm_ResetPullup()        do { WPUCbits. = 0; } while(0)
#define Alarm_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define Alarm_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define Alarm_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define Alarm_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC1 aliases
#define IO_RC1_TRIS                 TRISCbits.TRISC1
#define IO_RC1_LAT                  LATCbits.LATC1
#define IO_RC1_PORT                 PORTCbits.RC1
#define IO_RC1_WPU                  WPUCbits.
#define IO_RC1_OD                   ODCONCbits.
#define IO_RC1_ANS                  ANSELCbits.
#define IO_RC1_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_RC1_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_RC1_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_RC1_GetValue()           PORTCbits.RC1
#define IO_RC1_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_RC1_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define IO_RC1_SetPullup()          do { WPUCbits. = 1; } while(0)
#define IO_RC1_ResetPullup()        do { WPUCbits. = 0; } while(0)
#define IO_RC1_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define IO_RC1_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define IO_RC1_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC1_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC3 aliases
#define IO_RC3_TRIS                 TRISCbits.TRISC3
#define IO_RC3_LAT                  LATCbits.LATC3
#define IO_RC3_PORT                 PORTCbits.RC3
#define IO_RC3_WPU                  WPUCbits.
#define IO_RC3_OD                   ODCONCbits.
#define IO_RC3_ANS                  ANSELCbits.
#define IO_RC3_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_RC3_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_RC3_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_RC3_GetValue()           PORTCbits.RC3
#define IO_RC3_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_RC3_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_RC3_SetPullup()          do { WPUCbits. = 1; } while(0)
#define IO_RC3_ResetPullup()        do { WPUCbits. = 0; } while(0)
#define IO_RC3_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define IO_RC3_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define IO_RC3_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC3_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC4 aliases
#define IO_RC4_TRIS                 TRISCbits.TRISC4
#define IO_RC4_LAT                  LATCbits.LATC4
#define IO_RC4_PORT                 PORTCbits.RC4
#define IO_RC4_WPU                  WPUCbits.
#define IO_RC4_OD                   ODCONCbits.
#define IO_RC4_ANS                  ANSELCbits.
#define IO_RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_RC4_GetValue()           PORTCbits.RC4
#define IO_RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_RC4_SetPullup()          do { WPUCbits. = 1; } while(0)
#define IO_RC4_ResetPullup()        do { WPUCbits. = 0; } while(0)
#define IO_RC4_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define IO_RC4_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define IO_RC4_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC4_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RC7 aliases
#define IO_RC7_TRIS                 TRISCbits.TRISC7
#define IO_RC7_LAT                  LATCbits.LATC7
#define IO_RC7_PORT                 PORTCbits.RC7
#define IO_RC7_WPU                  WPUCbits.
#define IO_RC7_OD                   ODCONCbits.
#define IO_RC7_ANS                  ANSELCbits.
#define IO_RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define IO_RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define IO_RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define IO_RC7_GetValue()           PORTCbits.RC7
#define IO_RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define IO_RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define IO_RC7_SetPullup()          do { WPUCbits. = 1; } while(0)
#define IO_RC7_ResetPullup()        do { WPUCbits. = 0; } while(0)
#define IO_RC7_SetPushPull()        do { ODCONCbits. = 0; } while(0)
#define IO_RC7_SetOpenDrain()       do { ODCONCbits. = 1; } while(0)
#define IO_RC7_SetAnalogMode()      do { ANSELCbits. = 1; } while(0)
#define IO_RC7_SetDigitalMode()     do { ANSELCbits. = 0; } while(0)

// get/set RD2 aliases
#define Motor1_TRIS                 TRISDbits.TRISD2
#define Motor1_LAT                  LATDbits.LATD2
#define Motor1_PORT                 PORTDbits.RD2
#define Motor1_WPU                  WPUDbits.
#define Motor1_OD                   ODCONDbits.
#define Motor1_ANS                  ANSELDbits.
#define Motor1_SetHigh()            do { LATDbits.LATD2 = 1; } while(0)
#define Motor1_SetLow()             do { LATDbits.LATD2 = 0; } while(0)
#define Motor1_Toggle()             do { LATDbits.LATD2 = ~LATDbits.LATD2; } while(0)
#define Motor1_GetValue()           PORTDbits.RD2
#define Motor1_SetDigitalInput()    do { TRISDbits.TRISD2 = 1; } while(0)
#define Motor1_SetDigitalOutput()   do { TRISDbits.TRISD2 = 0; } while(0)
#define Motor1_SetPullup()          do { WPUDbits. = 1; } while(0)
#define Motor1_ResetPullup()        do { WPUDbits. = 0; } while(0)
#define Motor1_SetPushPull()        do { ODCONDbits. = 0; } while(0)
#define Motor1_SetOpenDrain()       do { ODCONDbits. = 1; } while(0)
#define Motor1_SetAnalogMode()      do { ANSELDbits. = 1; } while(0)
#define Motor1_SetDigitalMode()     do { ANSELDbits. = 0; } while(0)

// get/set RD3 aliases
#define Motor2_TRIS                 TRISDbits.TRISD3
#define Motor2_LAT                  LATDbits.LATD3
#define Motor2_PORT                 PORTDbits.RD3
#define Motor2_WPU                  WPUDbits.
#define Motor2_OD                   ODCONDbits.
#define Motor2_ANS                  ANSELDbits.
#define Motor2_SetHigh()            do { LATDbits.LATD3 = 1; } while(0)
#define Motor2_SetLow()             do { LATDbits.LATD3 = 0; } while(0)
#define Motor2_Toggle()             do { LATDbits.LATD3 = ~LATDbits.LATD3; } while(0)
#define Motor2_GetValue()           PORTDbits.RD3
#define Motor2_SetDigitalInput()    do { TRISDbits.TRISD3 = 1; } while(0)
#define Motor2_SetDigitalOutput()   do { TRISDbits.TRISD3 = 0; } while(0)
#define Motor2_SetPullup()          do { WPUDbits. = 1; } while(0)
#define Motor2_ResetPullup()        do { WPUDbits. = 0; } while(0)
#define Motor2_SetPushPull()        do { ODCONDbits. = 0; } while(0)
#define Motor2_SetOpenDrain()       do { ODCONDbits. = 1; } while(0)
#define Motor2_SetAnalogMode()      do { ANSELDbits. = 1; } while(0)
#define Motor2_SetDigitalMode()     do { ANSELDbits. = 0; } while(0)

/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/