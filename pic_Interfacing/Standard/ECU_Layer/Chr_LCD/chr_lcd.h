/* 
 * File:   chr_lcd.h
 * Author: Salah-Eldin
 * Description:
 * Header file for controlling a character LCD using a 4-bit interface and an 8-bit interface.
 * Created on September 2, 2024
 */

#ifndef CHR_LCD_H
#define CHR_LCD_H

//===================================
// Includes
//===================================
#include "chr_lcd_cfg.h"
#include "../../MCAL_Layer/GPIO/gpio.h"

//===================================
// Macro Declarations
//===================================
#define LCD_CLEAR                           0x01
#define LCD_RETURN_HOME                     0x02
#define LCD_ENTRY_MODE                      0x06
#define LCD_CURSOR_OFF_DISPLAY_ON           0x0C
#define LCD_CURSOR_OFF_DISPLAY_OFF          0x08
#define LCD_CURSOR_ON_BLINK_ON              0x0F
#define LCD_CURSOR_ON_BLINK_OFF             0x0E
#define LCD_DISPLAY_SHIFT_RIGHT             0x1C
#define LCD_DISPLAY_SHIFT_LEFT              0x18
#define LCD_8BIT_MODE_2_LINES               0x38
#define LCD_4BIT_MODE_2_LINES               0x28    
#define LCD_CGRAM_START                     0x40
#define LCD_DDRAM_START                     0x80

#define ROW1                                 1 
#define ROW2                                 2
#define ROW3                                 3 
#define ROW4                                 4 

#define ROW1_START                           0x80
#define ROW2_START                           0xC0
#define ROW3_START                           0x94 
#define ROW4_START                           0xD4 

#define FOUR_BIT_NUMBER                      4
#define EIGHT_BIT_NUMBER                     8

//===================================
// Data Types Declarations
//===================================
#if defined(FOUR_BIT_MODE)
typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
} lcd_4bit_t;
#elif defined(EIGHT_BIT_MODE)
typedef struct
{
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
} lcd_8bit_t;
#endif

//===================================
// Functions Declarations
//===================================

/**
 * @brief Initializes the 4-bit LCD.
 * @param lcd Pointer to the lcd_4bit_t structure containing the LCD configuration.
 * @return Status of the operation.
 */
#if defined(FOUR_BIT_MODE)
Std_ReturnType lcd_4bit_init(lcd_4bit_t *lcd);

/**
 * @brief Sends a command to the 4-bit LCD.
 * @param lcd Pointer to the lcd_4bit_t structure containing the LCD configuration.
 * @param cmd Command to be sent.
 * @return Status of the operation.
 */
Std_ReturnType lcd_4bit_send_cmd(const lcd_4bit_t *lcd, uint8 cmd);

/**
 * @brief Sends a character to the 4-bit LCD.
 * @param lcd Pointer to the lcd_4bit_t structure containing the LCD configuration.
 * @param data Character to be sent.
 * @return Status of the operation.
 */
Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t *lcd, uint8 data);

/**
 * @brief Sends a character to a specific position on the 4-bit LCD.
 * @param lcd Pointer to the lcd_4bit_t structure containing the LCD configuration.
 * @param data Character to be sent.
 * @param row Row number.
 * @param column Column number.
 * @return Status of the operation.
 */
Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t *lcd, uint8 data, uint8 row, uint8 column);

/**
 * @brief Sends a string to the 4-bit LCD.
 * @param lcd Pointer to the lcd_4bit_t structure containing the LCD configuration.
 * @param str String to be sent.
 * @return Status of the operation.
 */
Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str);

/**
 * @brief Sends a string to a specific position on the 4-bit LCD.
 * @param lcd Pointer to the lcd_4bit_t structure containing the LCD configuration.
 * @param str String to be sent.
 * @param row Row number.
 * @param column Column number.
 * @return Status of the operation.
 */
Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 *str, uint8 row, uint8 column);

/**
 * @brief Sends a custom character to a specific position on the 4-bit LCD.
 * @param lcd Pointer to the lcd_4bit_t structure containing the LCD configuration.
 * @param chr Custom character data.
 * @param row Row number.
 * @param column Column number.
 * @param mem_pos Memory position for custom character.
 * @return Status of the operation.
 */
Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, const uint8 chr[], 
                                        uint8 row, uint8 column, uint8 mem_pos);
#elif defined(EIGHT_BIT_MODE)
Std_ReturnType lcd_8bit_init(lcd_8bit_t *lcd);
Std_ReturnType lcd_8bit_send_cmd(const lcd_8bit_t *lcd, uint8 cmd);
Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t *lcd, uint8 data);
Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t *lcd, uint8 data, uint8 row, uint8 column);
Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str);
Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 *str, uint8 row, uint8 column);
Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, uint8 const chr[], 
                                        uint8 row, uint8 column, uint8 mem_pos);
#endif

/**
 * @brief Converts an 8-bit integer to a string.
 * @param value 8-bit integer value.
 * @param str Pointer to the string buffer.
 * @return Status of the operation.
 */
Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str);

/**
 * @brief Converts a 16-bit integer to a string.
 * @param value 16-bit integer value.
 * @param str Pointer to the string buffer.
 * @return Status of the operation.
 */
Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str);

/**
 * @brief Converts a 32-bit integer to a string.
 * @param value 32-bit integer value.
 * @param str Pointer to the string buffer.
 * @return Status of the operation.
 */
Std_ReturnType convert_uint32_to_string(uint32 value, uint16 *str);

#endif /* CHR_LCD_H */
