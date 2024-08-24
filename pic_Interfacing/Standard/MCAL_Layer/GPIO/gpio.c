/* 
 * File:   gpio.c
 * Author: Salah-Eldin
 * 
 * Description:
 * This source file provides the interface and data structures for controlling GPIO pins and ports.
 * The functions defined in this file allow setting the direction, writing logic levels, reading logic levels,
 * toggling, and initializing GPIO pins and ports. The header also defines various macros and enumerations
 * for easy manipulation of GPIO pins and ports.
 * 
 * Created on August 10, 2024
 */

//=========================================================================
//                             includes
//=========================================================================

#include "gpio.h"

//=========================================================================
//                           Global Variables
//=========================================================================

/* Reference to data direction control registers */
volatile uint8 *tris_registers[] = {&TRISA, &TRISB, &TRISC, &TRISD, &TRISE};
/* Reference to data latch registers (Read and Write to data latch) */
volatile uint8 *lat_registers[] = {&LATA, &LATB, &LATC, &LATD, &LATE};
/* Reference to port registers */
volatile uint8 *port_registers[] = {&PORTA, &PORTB, &PORTC, &PORTD, &PORTE};

//=========================================================================
//                         GPIO Function Definitions
//=========================================================================

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
/**
 * @brief Sets the direction of a GPIO pin.
 * 
 * This function configures the direction (input or output) of a specific GPIO pin based
 * on the information provided in the pin configuration structure.
 * 
 * @param pin A pointer to the pin configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_pin_set_direction(const pin_config_t *pin)
{
    Std_ReturnType ret = E_OK;

    if(NULL == pin || pin->pin_num > PORT_PIN_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (pin->direction)
        {
        case GPIO_DIRECTION_INPUT:
            SET_BIT(*tris_registers[pin->port], pin->pin_num);
            break;
        case GPIO_DIRECTION_OUTPUT:
            CLR_BIT(*tris_registers[pin->port], pin->pin_num);
            break;
        default:
            ret = E_NOT_OK;
            break;
        }
    }
    
    return ret;
}

/**
 * @brief Retrieves the direction (input or output) of a specific GPIO pin.
 * 
 * This function reads and returns the direction (input or output) of a specific GPIO pin
 * based on the provided pin configuration. It reads the corresponding bit in the TRIS register.
 * 
 * @param pin A pointer to the pin configuration structure.
 * @param direction_status Pointer to store the direction status (input or output).
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_pin_get_direction(const pin_config_t *pin, direction_t *direction_status)
{
    Std_ReturnType ret = E_OK;

    if(NULL == pin || NULL == direction_status || pin->pin_num > PORT_PIN_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = READ_BIT(*tris_registers[pin->port], pin->pin_num);
    }
    return ret;
}

/**
 * @brief Writes a logic level (high or low) to a specific GPIO pin.
 * 
 * This function writes a logic level (high or low) to a specific GPIO pin based on the provided
 * pin configuration. It sets or clears the corresponding bit in the LAT register to achieve
 * the desired logic level.
 * 
 * @param pin A pointer to the pin configuration structure.
 * @param logic The desired logic level (GPIO_HIGH or GPIO_LOW).
 * @return Std_ReturnType A status indicating the success or failure of the operation. 
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_pin_write(const pin_config_t *pin, logic_t logic)
{
    Std_ReturnType ret = E_OK;

    if(NULL == pin || pin->pin_num > PORT_PIN_MAX_NUM - 1) 
    {
        ret = E_NOT_OK;
    }
    else
    {
        switch (logic)
        {
        case GPIO_LOW:
            CLR_BIT(*lat_registers[pin->port], pin->pin_num);
            break;
        case GPIO_HIGH:
            CLR_BIT(*lat_registers[pin->port], pin->pin_num);
            SET_BIT(*lat_registers[pin->port], pin->pin_num);
            break;
        default:
            ret = E_NOT_OK;
            break;
        }
    }

    return ret;
}

/**
 * @brief Reads the logic level (high or low) of a specific GPIO pin.
 * 
 * This function reads and returns the logic level (high or low) of a specific GPIO pin
 * based on the provided pin configuration. It reads the corresponding bit in the PORT register.
 * 
 * @param pin A pointer to the pin configuration structure.
 * @param logic Pointer to store the logic level (GPIO_HIGH or GPIO_LOW).
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_pin_read(const pin_config_t *pin, logic_t *logic)
{
    Std_ReturnType ret = E_OK;

    if(NULL == pin || NULL == logic || pin->pin_num > PORT_PIN_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *logic = READ_BIT(*port_registers[pin->port], pin->pin_num);
    }

    return ret;
}

/**
 * @brief Toggles the logic level of a specific GPIO pin.
 * 
 * This function toggles (inverts) the logic level of a specific GPIO pin based on the provided
 * pin configuration. It XORs the corresponding bit in the LAT register to achieve the toggle effect.
 * 
 * @param pin A pointer to the pin configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_pin_toggle(const pin_config_t *pin)
{
    Std_ReturnType ret = E_OK;

    if(NULL == pin || pin->pin_num > PORT_PIN_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        TOG_BIT(*lat_registers[pin->port], pin->pin_num);
    }

    return ret;
}
#endif /* GPIO_PORT_PIN_CONFIGURATION */

#if GPIO_PORT_PIN_CONFIGURATION==CONFIG_ENABLE
/**
 * @brief Initializes a specific GPIO pin's direction and logic level.
 * 
 * This function initializes a specific GPIO pin's direction and logic level based on the provided
 * pin configuration. It sets the direction and logic level by calling the appropriate functions.
 * 
 * @param pin A pointer to the pin configuration structure.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_pin_initialize(const pin_config_t *pin)
{
    Std_ReturnType ret = E_OK;

    if(NULL == pin || pin->pin_num > PORT_PIN_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_set_direction(pin);
        ret = gpio_pin_write(pin, pin->logic);
    }

    return ret;
}

/**
 * @brief Sets the direction (input or output) of an entire GPIO port.
 * 
 * This function sets the direction (input or output) of an entire GPIO port by writing the specified
 * direction value to the corresponding TRIS register.
 * 
 * @param port The index of the port to configure.
 * @param direction The direction value to set for the entire port.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_port_set_direction(port_index_t port, uint8 direction)
{
    Std_ReturnType ret = E_OK;
    if(port > PORT_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *tris_registers[port] = direction;
    }

    return ret;
}

/**
 * @brief Retrieves the direction (input or output) status of an entire GPIO port.
 * 
 * This function reads and returns the direction (input or output) status of an entire GPIO port
 * based on the specified port index. It reads the corresponding TRIS register.
 * 
 * @param port The index of the port to query.
 * @param direction_status Pointer to store the direction status of the port.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_port_get_direction(port_index_t port, uint8 *direction_status)
{
    Std_ReturnType ret = E_OK;

    if(NULL == direction_status || port > PORT_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *direction_status = *tris_registers[port];
    }
    return ret;
}

/**
 * @brief Writes logic levels to an entire GPIO port.
 * 
 * This function writes logic levels to an entire GPIO port by setting the specified logic value
 * to the corresponding LAT register.
 * 
 * @param port The index of the port to configure.
 * @param value The logic value to write to the entire port.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_port_write(port_index_t port, uint8 value)
{
    Std_ReturnType ret = E_OK;

    if(port > PORT_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *lat_registers[port] = value;
    }

    return ret;
}

/**
 * @brief Reads logic levels from an entire GPIO port.
 * 
 * This function reads and returns the logic levels from an entire GPIO port based on the specified
 * port index. It reads the corresponding PORT register.
 * 
 * @param port The index of the port to query.
 * @param value Pointer to store the logic values read from the port.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *          - E_OK: The operation was successful.
 *          - E_NOT_OK: An error occurred during the operation.
 */
Std_ReturnType gpio_port_read(port_index_t port, uint8 *value)
{
    Std_ReturnType ret = E_OK;

    if(NULL == value || port > PORT_MAX_NUM - 1)
    {
        ret = E_NOT_OK;
    }
    else
    {
        *value = *port_registers[port];
    }

    return ret;
}
#endif /* GPIO_PORT_PIN_CONFIGURATION */
