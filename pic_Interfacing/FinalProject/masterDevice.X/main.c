/*
 * @file main.c
 * 
 * @brief Main application file for the system, handling real-time clock updates,
 *        temperature monitoring, and I2C EEPROM interactions.
 * 
 * @author Salah-Eldin
 * @version 1.0.2
 * @date 2024
 * 
 * @details This code initializes the system, manages global interrupts,
 *          handles temperature reading from a sensor, and updates/display
 *          time data. The temperature state is managed, and an alarm is triggered
 *          when certain thresholds are met. Data is saved to external EEPROM via I2C.
 */

/* Include necessary header files */
#include "mcc_generated_files/system/system.h"
#include "ECU_Layer/RTC/rtc.h"
#include "ECU_Layer/DISP/disp.h"
#include "../Shared/sharedData.h"

/* Define Macros */
#define TEMP_SENSOR_ADDR      0x4D        // I2C address for temperature sensor
#define EEPROM_ADDR           0x50        // I2C address for external EEPROM
#define SLAVE_MCU_ADDR        0x8         // I2C address for slave microcontroller
#define ALARM_THRESHOLD_IDLE   45          // Temperature threshold for idle state
#define ALARM_THRESHOLD_HIGH   50          // Temperature threshold for high state
#define EEPROM_DEFAULT_ADDR    0x08       // Default starting EEPROM address
#define EEPROM_INCREMENT       8           // EEPROM address increment value
#define TEMP_POLL_DELAY_MS     200        // Temperature polling delay in ms
#define EEPROM_DELAY_MS        10          // Delay after writing to EEPROM
#define EEPROM_READ_FAILURE    0xFF        // Default value for EEPROM read failure
#define TIMER_TICK_INIT        1           // Initial value of timer ticks
#define DATA_LENGTH            7           // Length of the data array

/* Boolean Macros */
#define TRUE    1
#define FALSE   0

/* Function Prototypes */
void timer0_int_handler(void);

/* Global Variables */
volatile uint8_t timerTicks = TIMER_TICK_INIT;       // Counter for timer ticks
volatile uint8_t timeDate[DATA_LENGTH] = {0};        // Array to hold time and date information
volatile uint8_t temperature = 0;                      // Current temperature reading
uint8_t temperatureAddress = 0x00;                     // Address for temperature sensor communication
uint8_t temperatureState = temp_state_idle;            // Current temperature state
uint8_t previousTemperatureState = temp_state_idle;    // Previous temperature state
uint8_t externalEEPROMAddress = 0x00;                  // Current EEPROM address for logging

/*
 * @brief Main function: entry point of the application
 */
int main(void) {
    /* ===========================
     *      System Initialization
     * =========================== */
    SYSTEM_Initialize();  // Initialize the system peripherals

    // Register timer interrupt callback
    Timer0_OverflowCallbackRegister(timer0_int_handler);

    // Enable Global and Peripheral Interrupts
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    
    // Initialize EEPROM address
    I2C1_WriteRead(EEPROM_ADDR, &externalEEPROMAddress, 1, &externalEEPROMAddress, 1);
    while (I2C1_IsBusy());

    if (externalEEPROMAddress == EEPROM_READ_FAILURE) {
        externalEEPROMAddress = EEPROM_DEFAULT_ADDR; // Set to default if read fails
    }

    /* ===========================
     *         Main Loop
     * =========================== */
    while (1) {
        // Check if a timer tick has occurred
        if (timerTicks) {
            timerTicks--;

            // Update RTC time and display it via UART
            rtc_update_time(timeDate);
            disp_display_uart_time_date(timeDate);
        }

        // Read temperature from sensor
        I2C1_WriteRead(TEMP_SENSOR_ADDR, &temperatureAddress, 1, &temperature, 1);
        while (I2C1_IsBusy());
        __delay_ms(TEMP_POLL_DELAY_MS);

        // Save previous temperature state
        previousTemperatureState = temperatureState;

        // Update temperature state based on sensor reading
        if (temperature <= ALARM_THRESHOLD_IDLE) {
            temperatureState = temp_state_idle;
        } else if (temperature <= ALARM_THRESHOLD_HIGH) {
            temperatureState = temp_state_high;
        } else {
            temperatureState = temp_state_max;
        }

        // If the temperature state has changed, communicate with slave MCU
        if (temperatureState != previousTemperatureState) {
            I2C1_Write(SLAVE_MCU_ADDR, &temperatureState, 1);
            while (I2C1_IsBusy());

            // Handle max temperature state and EEPROM logging
            if (temperatureState == temp_state_max) {
                Alarm_SetHigh();  // Trigger the alarm
                
                // Display
                disp_display_uart_ascii("Alarm!!\r");
                
                // Log critical temperature time and save to EEPROM
                timeDate[RESERVED] = timeDate[HOUR_IND];
                timeDate[HOUR_IND] = timeDate[MIN_IND];
                timeDate[MIN_IND] = timeDate[SEC_IND];
                timeDate[SEC_IND] = externalEEPROMAddress;  // Log current EEPROM address
                externalEEPROMAddress += EEPROM_INCREMENT;   // Increment EEPROM address for next write

                I2C1_Write(EEPROM_ADDR, &timeDate, DATA_LENGTH); // Save time data to EEPROM
                while (I2C1_IsBusy());
                __delay_ms(EEPROM_DELAY_MS);

                // Save updated EEPROM address pointer
                timeDate[SEC_IND] = 0x00; // Reset seconds for EEPROM
                timeDate[MIN_IND] = externalEEPROMAddress; // Update EEPROM address in timeDate
                I2C1_Write(EEPROM_ADDR, &timeDate, 2); // Save updated address
                while (I2C1_IsBusy());
                __delay_ms(EEPROM_DELAY_MS);
            } else {
                Alarm_SetLow();  // Reset the alarm if not in max state
            }
        }
    }
}

/*
 * @brief Timer 0 interrupt handler to increment timer ticks
 */
void timer0_int_handler(void) {
    timerTicks++;  // Increment the timer ticks
}
