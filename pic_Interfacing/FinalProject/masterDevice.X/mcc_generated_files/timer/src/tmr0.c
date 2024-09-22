/**
 * TMR0 Generated Driver File
 * 
 * @file tmr0.c
 * 
 * @ingroup tmr0
 * 
 * @brief  Driver implementation for the TMR0 driver
 *
 * @version TMR0 Driver Version 1.0.0
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

#include <xc.h>
#include "../tmr0.h"

volatile uint16_t timer0ReloadVal;

const struct TMR_INTERFACE Timer0 = {
    .Initialize = Timer0_Initialize,
    .Start = Timer0_Start,
    .Stop = Timer0_Stop,
    .PeriodCountSet = Timer0_PeriodCountSet,
    .TimeoutCallbackRegister = Timer0_OverflowCallbackRegister,
    .Tasks = NULL
};

static void (*Timer0_OverflowCallback)(void);
static void Timer0_DefaultOverflowCallback(void);

void Timer0_Initialize(void)
{
    //Enable 16bit timer mode before assigning value to TMR0H
    T0CONbits.T08BIT = 0;

    //TMR0H 194; 
    TMR0H = 0xC2;

    //TMR0L 247; 
    TMR0L = 0xF7;

    //Load TMR0 value to the 16-bit reload variable
    timer0ReloadVal = ((uint16_t)TMR0H << 8) | TMR0L;

    //Clear Interrupt flag before enabling the interrupt
    INTCONbits.TMR0IF = 0;
	
    //Enable TMR0 interrupt.
    INTCONbits.TMR0IE = 1;

    //PS 1:128; PSA assigned; TMRSE Increment_hi_lo; TMRCS FOSC/4; T08BIT 16-bit; TMR0ON enabled; 
    T0CON = 0x96;

    //Set default callback for TMR0 overflow interrupt
    Timer0_OverflowCallbackRegister(Timer0_DefaultOverflowCallback);
}

void Timer0_Start(void)
{
    // Start the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 1;
}

void Timer0_Stop(void)
{
    // Stop the Timer by writing to TMR0ON bit
    T0CONbits.TMR0ON = 0;
}

uint16_t Timer0_Read(void)
{
    uint16_t readVal;
    uint8_t readValLow;
    uint8_t readValHigh;

    readValLow = TMR0L;
    readValHigh = TMR0H;
    readVal = ((uint16_t)readValHigh << 8) + readValLow;

    return readVal;
}

void Timer0_Write(size_t timerVal)
{
    // Write to the Timer0 register
    TMR0H = timerVal >> 8;
    TMR0L = (uint8_t) timerVal;
}

void Timer0_Reload(void)
{
    // Write to the Timer0 register
    TMR0H = timer0ReloadVal >> 8;
    TMR0L = (uint8_t) timer0ReloadVal;
}

void Timer0_PeriodCountSet(size_t periodVal)
{
   timer0ReloadVal = (uint16_t) periodVal;
}

void Timer0_OverflowISR(void)
{
    //Clear the TMR0 interrupt flag
    INTCONbits.TMR0IF = 0;

    //Reload TMR0
    //Write to the Timer0 register
    TMR0H = timer0ReloadVal >> 8;
    TMR0L = (uint8_t) timer0ReloadVal;

    if(Timer0_OverflowCallback)
    {
        Timer0_OverflowCallback();
    }
}

void Timer0_OverflowCallbackRegister(void (*CallbackHandler)(void))
{
    Timer0_OverflowCallback = CallbackHandler;
}

static void Timer0_DefaultOverflowCallback(void)
{
    //Add your interrupt code here or
    //Use Timer0_OverflowCallbackRegister function to use Custom ISR
}

