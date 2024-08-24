/* 
 * File:   led.c
 * Author: Salah-Eldin
 * 
 * Description:
 * This source file contains the implementation of LED control functions. The functions defined in this file
 * allow initializing an LED, turning it on, turning it off, and toggling its state based on the provided LED configuration.
 * 
 * Created on August 10, 2024
 */

//=========================================================================
//                              Includes
//=========================================================================

#include "led.h"

//=========================================================================
//                          Function Definitions
//=========================================================================

/**
 * @brief Initializes the assigned pin to be OUTPUT 
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_init(const led_t *led) {
    Std_ReturnType ret = E_OK;

    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin ={
            .port = led->port,
            .pin_num = led->pin,
            .direction = GPIO_DIRECTION_OUTPUT,
            .logic = led->led_status ^ led->connection
        };
        ret = gpio_pin_initialize(&pin);
    }

    return ret;
}

/**
 * @brief Turns on the LED based on the provided LED configuration.
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_turn_on(const led_t *led) {
    Std_ReturnType ret = E_OK;

    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin ={
            .port = led->port,
            .pin_num = led->pin
        };
        ret = gpio_pin_write(&pin, GPIO_HIGH ^ led->connection);
    }

    return ret;
}

/**
 * @brief Turns off the LED based on the provided LED configuration.
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_turn_off(const led_t *led) {
    Std_ReturnType ret = E_OK;

    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin ={
            .port = led->port,
            .pin_num = led->pin
        };
        ret = gpio_pin_write(&pin, GPIO_LOW ^ led->connection);
    }

    return ret;
}

/**
 * @brief Toggles the LED state based on the provided LED configuration.
 * 
 * @param led A pointer to the LED configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType led_toggle(const led_t *led) {
    Std_ReturnType ret = E_OK;

    if (NULL == led) {
        ret = E_NOT_OK;
    } else {
        pin_config_t pin ={
            .port = led->port,
            .pin_num = led->pin
        };
        ret = gpio_pin_toggle(&pin);
    }

    return ret;
}
