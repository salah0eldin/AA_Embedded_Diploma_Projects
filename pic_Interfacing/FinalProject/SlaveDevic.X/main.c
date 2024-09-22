/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @author Salah-Eldin
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
 */

#include "mcc_generated_files/system/system.h"
#include "../Shared/sharedData.h"

/* 
 * ===========================
 *        Macros
 * ===========================
 */
#define IDLE_DUTY_CYCLE     (155.5 * 4 * 0.5)   // Duty cycle for idle temperature state
#define HIGH_DUTY_CYCLE     (155.5 * 4 * 0.75)  // Duty cycle for high temperature state
#define MAX_DUTY_CYCLE      (155.5 * 4)         // Duty cycle for maximum temperature state

#define TRUE    1
#define FALSE   0

/* 
 * ===========================
 *        Global Variables
 * ===========================
 */
volatile uint8_t i2c_received_data;          // Stores data received from the I2C bus
volatile uint8_t i2c_interrupt_counter = 0;  // Counts the number of I2C interrupts

/* 
 * ===========================
 *        I2C Callback
 * ===========================
 */
bool I2C_InterruptHandler(i2c_client_transfer_event_t clientEvent) {
    i2c_interrupt_counter++;  // Increment interrupt counter on every I2C event
    if (clientEvent == I2C_CLIENT_TRANSFER_EVENT_RX_READY) {
        i2c_received_data = SSPBUF;  // Read data from the I2C buffer when it's ready
    }
}

/* 
 * ===========================
 *      Main Application
 * ===========================
 */
int main(void) {

    /* ===========================
     *      System Initialization
     * ===========================
     */
    SYSTEM_Initialize();  // Call the generated system initialization routine
    I2C1_CallbackRegister(I2C_InterruptHandler);  // Register the I2C interrupt handler

    INTERRUPT_GlobalInterruptEnable();   // Enable global interrupts
    INTERRUPT_PeripheralInterruptEnable();  // Enable peripheral interrupts

    // Initial motor direction
    Motor1_SetHigh(); 
    Motor2_SetLow();   
    
    uint8_t toggle_dir_flag = FALSE;  // Flag to track motor direction toggling, uses TRUE/FALSE

    /* ===========================
     *         Main Loop
     * ===========================
     */
    while (1) {
        // Check button status (IO_RC7) for toggling motors
        if (!(IO_RC7_GetValue())) {  // If button is pressed (value is low)
            if (toggle_dir_flag == FALSE) {  // Use FALSE to check if the flag is cleared
                toggle_dir_flag = TRUE;  // Set the flag to TRUE when motors are toggled
                Motor1_Toggle();      // Toggle Motor1
                Motor2_Toggle();      // Toggle Motor2
            }
        } else {
            toggle_dir_flag = FALSE;  // Reset the flag to FALSE when the button is released
        }

        // Handle I2C interrupt events
        if (i2c_interrupt_counter) {  // If an I2C interrupt has occurred
            i2c_interrupt_counter--;  // Decrement the interrupt counter
            Alarm_SetLow();           // Set the alarm to low by default
            
            // Adjust duty cycle based on the received I2C data
            switch (i2c_received_data) {
                case temp_state_idle:   // Idle state: set the duty cycle for idle temperature
                    CCP2_LoadDutyValue(IDLE_DUTY_CYCLE);
                    break;
                case temp_state_high:   // High state: set the duty cycle for high temperature
                    CCP2_LoadDutyValue(HIGH_DUTY_CYCLE);
                    break;
                case temp_state_max:    // Max state: set the duty cycle for maximum temperature
                    CCP2_LoadDutyValue(MAX_DUTY_CYCLE);
                    Alarm_SetHigh();    // Set the alarm to high in maximum state
                    break;
            }
        }
    }
}
