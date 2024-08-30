/* 
 * File:   timer0.c
 * Author: Salah-Eldin
 *
 * Created on August 29, 2024
 */

//==================================================
// Includes
//==================================================
#include "timer0.h"

//==================================================
// Statics
//==================================================
#if TIMER0_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
static void (*TIMR0_InterruptHandler)(void) = NULL;
#endif

static inline void Timer0_Prescaler_Config(const timer0_t *timer0);
static inline void Timer0_Mode_Select(const timer0_t *timer0);
static inline void Timer0_Set_Register_Size(const timer0_t *timer0);

static uint16 preload = ZERO_INIT;

//==================================================
// Function Definitions
//==================================================

/**
 * @brief Initializes Timer0 based on the provided configuration.
 * 
 * @param timer0 A pointer to the Timer0 configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType Timer0_Init(const timer0_t *timer0) {
    Std_ReturnType ret = E_OK;

    if (NULL == timer0) {
        ret = E_NOT_OK;
    } else {
        //Disable the Timer0 Module
        TIMER0_MODULE_DISABLE();
        //Configure the Prescaler
        Timer0_Prescaler_Config(timer0);
        //Select the Timer0 Mode
        Timer0_Mode_Select(timer0);
        //Select the data register size of timer0 (8bits or 16bits)
        Timer0_Set_Register_Size(timer0);
        //Write preload value if there is.
        TMR0H = (timer0->preload >> 8);
        TMR0L = (uint8) (timer0->preload);
        //Store the preload value 
        preload = timer0->preload;

        //Configure the interrupt
#if TIMER0_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_ENABLE();
        TIMER0_INTERRUPT_FLAG_CLEAR();
        TIMR0_InterruptHandler = timer0->TIMR0_InterruptHandler;
        //Interrupt priority configurations
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
        INTERRUPT_PriorityLevelsEnable();
        if (INTERRUPT_HIGH_PRIORITY == timer0->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            TIMER0_INT_HIGH_PRIORITY();
        } else if (INTERRUPT_LOW_PRIORITY == timer0->priority) {
            INTERRUPT_GlobalInterruptHighEnable();
            INTERRUPT_GlobalInterruptLowEnable();
            TIMER0_INT_LOW_PRIORITY();
        } else {
            /* Nothing */
        }
#else 
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif
#endif
        //Enable the Timer0 Module
        TIMER0_MODULE_ENABLE();
    }
    return ret;
}

/**
 * @brief De-Initializes the Timer0 Module.
 * 
 * @param timer0 A pointer to the Timer0 configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType Timer0_DeInit(const timer0_t *timer0) {
    Std_ReturnType ret = E_OK;

    if (NULL == timer0) {
        ret = E_NOT_OK;
    } else {
        //Disable Timer0 Module
        TIMER0_MODULE_DISABLE();
        //Disable Timer0 Interrupt
#if TIMER0_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
        TIMER0_INTERRUPT_DISABLE();
#endif
    }
    return ret;
}

/**
 * @brief Writes a 16-bit value to Timer0. 
 * 
 * @param timer0 A pointer to the Timer0 configuration structure.
 * @param val The 16-bit value to write to Timer0.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType Timer0_Write_Value(const timer0_t *timer0, uint16 val) {
    Std_ReturnType ret = E_OK;

    if (NULL == timer0) {
        ret = E_NOT_OK;
    } else {
        TMR0H = (uint8) (val >> 8);
        TMR0L = (uint8) (val);
    }
    return ret;
}

/**
 * @brief Reads a 16-bit value from Timer0.
 * 
 * @param timer0 A pointer to the Timer0 configuration structure.
 * @param val A pointer to store the value.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType Timer0_Read(const timer0_t *timer0, uint16 *val) {
    Std_ReturnType ret = E_OK;
    uint8 l_tmr0l = ZERO_INIT, l_tmr0h = ZERO_INIT;

    if (NULL == timer0 || NULL == val) {
        ret = E_NOT_OK;
    } else {
        l_tmr0l = TMR0L;
        l_tmr0h = TMR0H;
        *val = (uint16) ((l_tmr0h << 8) + l_tmr0l);
    }
    return ret;
}

//==================================================
// Static Definitions
//==================================================
/**
 * @brief Helper function to configure the Prescaler value.
 * 
 * @param timer0 A pointer to the Timer0 configuration structure.
 */
static inline void Timer0_Prescaler_Config(const timer0_t *timer0) {
    if (TIMER0_PRESCALER_ENABLE_CFG == timer0->prescaler_status) {
        TIMER0_PRESCALER_ENABLE();
        T0CONbits.T0PS = timer0->prescaler_val;
    } else if (TIMER0_PRESCALER_DISABLE_CFG == timer0->prescaler_status) {
        TIMER0_PRESCALER_DISABLE();
    } else {
        /* Nothing */
    }
}

/**
 * @brief Helper function to select the mode (Timer or Counter).
 * 
 * @param timer0 A pointer to the Timer0 configuration structure.
 */
static inline void Timer0_Mode_Select(const timer0_t *timer0) {
    if (TIMER0_TIMER_MODE == timer0->mode) {
        TIMER0_TIMER_MODE_ENABLE();
    } else if (TIMER0_COUNTER_MODE == timer0->mode) {
        TIMER0_COUNTER_MODE_ENABLE();
        if (TIMER0_RISING_EDGE_CFG == timer0->counter_edge) {
            TIMER0_RISING_EDGE_SELECT();
        }
        else if (TIMER0_FALLING_EDGE_CFG == timer0->counter_edge) {
            TIMER0_FALLING_EDGE_SELECT();
        } else {
            /* Nothing */
        }
    } else {
        /* Nothing */
    }
}

/**
 * @brief Helper function to configure Timer0 as 8-bits or 16-bits. 
 * 
 * @param timer0 A pointer to the Timer0 configuration structure.
 */
static inline void Timer0_Set_Register_Size(const timer0_t *timer0) {
    if (TIMER0_8BIT_REGISTER_MODE == timer0->reg_size) {
        TIMER0_8BIT_REGISTER_MODE_ENABLE();
    } else if (TIMER0_16BIT_REGISTER_MODE == timer0->reg_size) {
        TIMER0_16BIT_REGISTER_MODE_ENABLE();
    } else {
        /* Nothing */
    }

}

//==================================================
// ISR Function
//==================================================

/**
 * @brief The Timer0 interrupt MCAL helper function
 * 
 */
void TIMR0_ISR(void) {
#if TIMER0_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
    //Timer0 interrupt occurred, the flag must be cleared.
    TIMER0_INTERRUPT_FLAG_CLEAR();
    //Write the preload value every time this ISR executes.
    TMR0H = (uint8) (preload >> 8);
    TMR0L = (uint8) (preload);
    //CallBack func gets called every time this ISR executes.
    if (TIMR0_InterruptHandler) {
        TIMR0_InterruptHandler();
    } else {
        /* Nothing */
    }
#endif
}