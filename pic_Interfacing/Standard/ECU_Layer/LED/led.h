/* 
 * File:   led.h
 * Author: Salah-Eldin
 * 
 * Description:
 * This header file defines the interface for controlling LEDs based on a provided LED configuration. 
 * The LED configuration includes the port, pin, and initial status (ON or OFF) of the LED. The functions defined here allow initializing an LED, turning it on, turning it off, and toggling its state.
 * 
 * Created on August 10, 2024
 */

#ifndef LED_H
#define LED_H

//=========================================================================
//                              Includes
//=========================================================================
#include "../../MCAL_Layer/GPIO/gpio.h"
#include "led_config.h"

//=========================================================================
//                           Macro Declarations
//=========================================================================

//=========================================================================
//                       Macro Functions Declarations
//=========================================================================

//=========================================================================
//                           Data Types Declarations
//=========================================================================
typedef enum {
    LED_OFF = 0,
    LED_ON
} led_status;

typedef enum {
    LED_POSITIVE = 0,
    LED_NEGATIVE
} led_connection;

typedef struct {
    uint8 port : 3;
    uint8 pin : 3;
    uint8 connection : 1;
    uint8 led_status : 1;
} led_t;

//=========================================================================
//                           Function Declarations
//=========================================================================
/**
 * @brief Initializes the assigned pin to be OUTPUT.
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_init(const led_t *led);

/**
 * @brief Turns on the LED based on the provided LED configuration.
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_turn_on(const led_t *led);

/**
 * @brief Turns off the LED based on the provided LED configuration.
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_turn_off(const led_t *led);

/**
 * @brief Toggles the LED state based on the provided LED configuration.
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_toggle(const led_t *led);

#endif	/* LED_H */
