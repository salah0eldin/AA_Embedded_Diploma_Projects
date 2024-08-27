/* 
 * File:   chr_lcd.c
 * Author: Salah-Eldin
 * Description:
 * Source file for controlling a character LCD using a 4-bit interface and a 8-bit interface.
 * Created on September 2, 2024
 */

#include "chr_lcd.h"

//==============================================================
//                    Static Function Declarations
//==============================================================

#if defined(FOUR_BIT_MODE)
static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd, uint8 _data_cmd);
static Std_ReturnType lcd_4bits_send_enable_signal(const lcd_4bit_t *lcd);
static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 column);
#elif defined(EIGHT_BIT_MODE)
static Std_ReturnType lcd_8bits_send_enable_signal(const lcd_8bit_t *lcd);
static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column);
#endif

//==============================================================
//                    4-Bit Mode Implementation
//==============================================================

#if defined(FOUR_BIT_MODE)

Std_ReturnType lcd_4bit_init(lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    uint8 pins_counter = ZERO_INIT;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        lcd->lcd_rs.direction = GPIO_DIRECTION_OUTPUT;
        lcd->lcd_rs.logic = GPIO_LOW;
        lcd->lcd_en.direction = GPIO_DIRECTION_OUTPUT;
        lcd->lcd_en.logic = GPIO_LOW;

        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for (pins_counter = ZERO_INIT; pins_counter < FOUR_BIT_NUMBER; pins_counter++) {
            lcd->lcd_data[pins_counter].direction = GPIO_DIRECTION_OUTPUT;
            lcd->lcd_data[pins_counter].logic = GPIO_LOW;
            ret = gpio_pin_initialize(&(lcd->lcd_data[pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_cmd(lcd, LCD_8BIT_MODE_2_LINES);
        __delay_ms(5);
        ret = lcd_4bit_send_cmd(lcd, LCD_8BIT_MODE_2_LINES);
        __delay_us(120);
        ret = lcd_4bit_send_cmd(lcd, LCD_8BIT_MODE_2_LINES);

        ret = lcd_4bit_send_cmd(lcd, LCD_CLEAR);
        __delay_ms(1);
        ret = lcd_4bit_send_cmd(lcd, LCD_RETURN_HOME);
        ret = lcd_4bit_send_cmd(lcd, LCD_ENTRY_MODE);
        ret = lcd_4bit_send_cmd(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_cmd(lcd, LCD_4BIT_MODE_2_LINES);
        ret = lcd_4bit_send_cmd(lcd, LCD_DDRAM_START);
    }
    return ret;
}

//==============================================================
//                4-Bit Mode Command Functions
//==============================================================

Std_ReturnType lcd_4bit_send_cmd(const lcd_4bit_t *lcd, uint8 cmd) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write(&(lcd->lcd_rs), GPIO_LOW);

        ret = lcd_send_4bits(lcd, cmd >> FOUR_BIT_NUMBER);
        ret = lcd_4bits_send_enable_signal(lcd);

        ret = lcd_send_4bits(lcd, cmd);
        ret = lcd_4bits_send_enable_signal(lcd);
    }
    return ret;
}

//==============================================================
//                4-Bit Mode Character Functions
//==============================================================

Std_ReturnType lcd_4bit_send_char(const lcd_4bit_t *lcd, uint8 data) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write(&(lcd->lcd_rs), GPIO_HIGH);

        ret = lcd_send_4bits(lcd, data >> FOUR_BIT_NUMBER);
        ret = lcd_4bits_send_enable_signal(lcd);

        ret = lcd_send_4bits(lcd, data);
        ret = lcd_4bits_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_char_pos(const lcd_4bit_t *lcd, uint8 data, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char(lcd, data);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string(const lcd_4bit_t *lcd, uint8 *str) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd || NULL == str) {
        ret = E_NOT_OK;
    } else {
        while (*str) {
            ret = lcd_4bit_send_char(lcd, *str++);
        }
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_string_pos(const lcd_4bit_t *lcd, uint8 *str, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd || NULL == str) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_string(lcd, str);
    }
    return ret;
}

Std_ReturnType lcd_4bit_send_custom_char(const lcd_4bit_t *lcd, const uint8 chr[],
        uint8 row, uint8 column, uint8 mem_pos) {
    Std_ReturnType ret = E_OK;
    uint8 l_counter = ZERO_INIT;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_4bit_send_cmd(lcd, LCD_CGRAM_START + (mem_pos * 8));
        for (l_counter = ZERO_INIT; l_counter < 7; l_counter++) {
            ret = lcd_4bit_send_char(lcd, chr[l_counter]);
        }
        ret = lcd_4bit_send_char_pos(lcd, mem_pos, row, column);
    }
    return ret;
}

#elif defined(EIGHT_BIT_MODE)

//==============================================================
//                    8-Bit Mode Implementation
//==============================================================

Std_ReturnType lcd_8bit_init(const lcd_8bit_t *lcd) {
    Std_ReturnType ret = E_OK;
    uint8 pins_counter = ZERO_INIT;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        lcd->lcd_rs.direction = GPIO_DIRECTION_OUTPUT;
        lcd->lcd_rs.logic = GPIO_LOW;
        lcd->lcd_en.direction = GPIO_DIRECTION_OUTPUT;
        lcd->lcd_en.logic = GPIO_LOW;
        
        ret = gpio_pin_initialize(&(lcd->lcd_rs));
        ret = gpio_pin_initialize(&(lcd->lcd_en));
        for (pins_counter = ZERO_INIT; pins_counter < EIGHT_BIT_NUMBER; pins_counter++) {
            lcd->lcd_data[pins_counter].direction = GPIO_DIRECTION_OUTPUT;
            lcd->lcd_data[pins_counter].logic = GPIO_LOW;
            gpio_pin_initialize(&(lcd->lcd_data[pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_cmd(lcd, LCD_8BIT_MODE_2_LINES);
        __delay_ms(5);
        ret = lcd_8bit_send_cmd(lcd, LCD_8BIT_MODE_2_LINES);
        __delay_us(120);
        ret = lcd_8bit_send_cmd(lcd, LCD_8BIT_MODE_2_LINES);

        ret = lcd_8bit_send_cmd(lcd, LCD_CLEAR);
        __delay_ms(1);
        ret = lcd_8bit_send_cmd(lcd, LCD_RETURN_HOME);
        ret = lcd_8bit_send_cmd(lcd, LCD_ENTRY_MODE);
        ret = lcd_8bit_send_cmd(lcd, LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_cmd(lcd, LCD_DDRAM_START);
    }
    return ret;
}

//==============================================================
//                8-Bit Mode Command Functions
//==============================================================

Std_ReturnType lcd_8bit_send_cmd(const lcd_8bit_t *lcd, uint8 cmd) {
    Std_ReturnType ret = E_OK;
    uint8 pins_counter = ZERO_INIT;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write(&(lcd->lcd_rs), GPIO_LOW);
        for (pins_counter = ZERO_INIT; pins_counter < EIGHT_BIT_NUMBER; pins_counter++) {
            gpio_pin_write(&(lcd->lcd_data[pins_counter]), (cmd >> pins_counter) & 0x01);
        }
        ret = lcd_8bits_send_enable_signal(lcd);
    }
    return ret;
}

//==============================================================
//                8-Bit Mode Character Functions
//==============================================================

Std_ReturnType lcd_8bit_send_char(const lcd_8bit_t *lcd, uint8 data) {
    Std_ReturnType ret = E_OK;
    uint8 pins_counter = ZERO_INIT;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write(&(lcd->lcd_rs), GPIO_HIGH);
        for (pins_counter = ZERO_INIT; pins_counter < 8; pins_counter++) {
            gpio_pin_write(&(lcd->lcd_data[pins_counter]), (data >> pins_counter) & 0x01);
        }
        ret = lcd_8bits_send_enable_signal(lcd);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_char_pos(const lcd_8bit_t *lcd, uint8 data, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char(lcd, data);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string(const lcd_8bit_t *lcd, uint8 *str) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd || NULL == str) {
        ret = E_NOT_OK;
    } else {
        while (*str) {
            ret = lcd_8bit_send_char(lcd, *str++);
        }
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_string_pos(const lcd_8bit_t *lcd, uint8 *str, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd || NULL == str) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_string(lcd, str);
    }
    return ret;
}

Std_ReturnType lcd_8bit_send_custom_char(const lcd_8bit_t *lcd, const uint8 chr[],
        uint8 row, uint8 column, uint8 mem_pos) {
    Std_ReturnType ret = E_OK;
    uint8 l_counter = ZERO_INIT;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = lcd_8bit_send_cmd(lcd, LCD_CGRAM_START + (mem_pos * 8));
        for (l_counter = ZERO_INIT; l_counter < 7; l_counter++) {
            ret = lcd_8bit_send_char(lcd, chr[l_counter]);
        }
        ret = lcd_8bit_send_char_pos(lcd, mem_pos, row, column);
    }
    return ret;
}

#endif

//==============================================================
//                     Static Function Definitions
//==============================================================

#if defined(FOUR_BIT_MODE)

static Std_ReturnType lcd_send_4bits(const lcd_4bit_t *lcd, uint8 _data_cmd) {
    Std_ReturnType ret = E_OK;
    uint8 l_pin_counter = ZERO_INIT;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        for (l_pin_counter = ZERO_INIT; l_pin_counter < FOUR_BIT_NUMBER; l_pin_counter++) {
            ret = gpio_pin_write(&(lcd->lcd_data[l_pin_counter]), (_data_cmd >> l_pin_counter) & 0x01);
        }
    }
    return ret;
}

static Std_ReturnType lcd_4bits_send_enable_signal(const lcd_4bit_t *lcd) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_4bit_set_cursor(const lcd_4bit_t *lcd, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;
    column--;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        switch (row) {
            case ROW1:
                ret = lcd_4bit_send_cmd(lcd, (ROW1_START + column));
                break;
            case ROW2:
                ret = lcd_4bit_send_cmd(lcd, (ROW2_START + column));
                break;
            case ROW3:
                ret = lcd_4bit_send_cmd(lcd, (ROW3_START + column));
                break;
            case ROW4:
                ret = lcd_4bit_send_cmd(lcd, (ROW4_START + column));
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

#elif defined(EIGHT_BIT_MODE)

static Std_ReturnType lcd_8bits_send_enable_signal(const lcd_8bit_t *lcd) {
    Std_ReturnType ret = E_OK;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        ret = gpio_pin_write(&(lcd->lcd_en), GPIO_HIGH);
        __delay_us(5);
        ret = gpio_pin_write(&(lcd->lcd_en), GPIO_LOW);
    }
    return ret;
}

static Std_ReturnType lcd_8bit_set_cursor(const lcd_8bit_t *lcd, uint8 row, uint8 column) {
    Std_ReturnType ret = E_OK;
    column--;

    if (NULL == lcd) {
        ret = E_NOT_OK;
    } else {
        switch (row) {
            case ROW1:
                ret = lcd_8bit_send_cmd(lcd, (ROW1_START + column));
                break;
            case ROW2:
                ret = lcd_8bit_send_cmd(lcd, (ROW2_START + column));
                break;
            case ROW3:
                ret = lcd_8bit_send_cmd(lcd, (ROW3_START + column));
                break;
            case ROW4:
                ret = lcd_8bit_send_cmd(lcd, (ROW4_START + column));
                break;
            default:
                ret = E_NOT_OK;
                break;
        }
    }
    return ret;
}

#endif

Std_ReturnType convert_uint8_to_string(uint8 value, uint8 *str){
    Std_ReturnType ret = E_OK;

    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str,0,4);
        sprintf(str,"%d",value);
    }
    
    return ret;
}

Std_ReturnType convert_uint16_to_string(uint16 value, uint8 *str){
    Std_ReturnType ret = E_OK;

    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str,0,6);
        sprintf(str,"%d",value);
    }
    
    return ret;
}

Std_ReturnType convert_uint32_to_string(uint32 value, uint16 *str){
    Std_ReturnType ret = E_OK;

    if (NULL == str) {
        ret = E_NOT_OK;
    } else {
        memset(str,0,11);
        sprintf(str,"%d",value);
    }
    
    return ret;
}
