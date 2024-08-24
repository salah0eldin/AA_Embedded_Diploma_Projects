/* 
 * File:   button.h
 * Author: Salah-Eldin
 * 
 * Description:
 * This header file provides an interface for working with buttons using GPIO pins. 
 * It defines data structures for button configurations, states, and active states.
 * Additionally, it declares functions to initialize and read the state of buttons, supporting both active-high and active-low configurations.
 * 
 * Created on August 11, 2024
 */

#ifndef BUTTON_H
#define BUTTON_H

//=========================================================================
//                           Includes
//=========================================================================

#include "../../MCAL_Layer/GPIO/gpio.h"
#include "button_cfg.h"

//=========================================================================
//                           Macro Declarations
//=========================================================================

//=========================================================================
//                           Macro Functions Declarations
//=========================================================================

//=========================================================================
//                           Data Types Declarations
//=========================================================================

typedef enum
{
    BUTTON_PRESSED,
    BUTTON_RELEASED        
} button_state_t;

typedef enum
{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
} button_active_t;

typedef struct
{
    pin_config_t pin;
    button_state_t state;
    button_active_t button_connection;
} button_t;

//=========================================================================
//                           Functions Declarations
//=========================================================================

/**
 * @brief Initializes the assigned pin to be INPUT.
 * 
 * @param btn A pointer to the button configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType button_init(const button_t *btn);

/**
 * @brief Reads the state of the button.
 * 
 * @param btn A pointer to the button configuration structure.
 * @param state Retrieves the button state.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType button_read_state(const button_t *btn, button_state_t *state);

#endif /* BUTTON_H */
