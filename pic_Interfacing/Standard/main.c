/* 
 * File:   main.c
 * Author: Salah-Eldin
 *
 * Created on August 10, 2024, 10:32 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "APP/application.h"

led_t led1 = {
    .port = PORTA_INDEX,
    .pin = PIN0,
    .connection = LED_POSITIVE,
    .led_status = LED_ON
};

seg_t seg1 = {
    .seg_pins[SEGMENT_PIN0].port = PORTC_INDEX,
    .seg_pins[SEGMENT_PIN0].pin_num = PIN0,
    .seg_pins[SEGMENT_PIN0].direction = GPIO_DIRECTION_OUTPUT,
    .seg_pins[SEGMENT_PIN0].logic = GPIO_HIGH,

    .seg_pins[SEGMENT_PIN1].port = PORTC_INDEX,
    .seg_pins[SEGMENT_PIN1].pin_num = PIN1,
    .seg_pins[SEGMENT_PIN1].direction = GPIO_DIRECTION_OUTPUT,
    .seg_pins[SEGMENT_PIN1].logic = GPIO_HIGH,

    .seg_pins[SEGMENT_PIN2].port = PORTC_INDEX,
    .seg_pins[SEGMENT_PIN2].pin_num = PIN2,
    .seg_pins[SEGMENT_PIN2].direction = GPIO_DIRECTION_OUTPUT,
    .seg_pins[SEGMENT_PIN2].logic = GPIO_HIGH,

    .seg_pins[SEGMENT_PIN3].port = PORTC_INDEX,
    .seg_pins[SEGMENT_PIN3].pin_num = PIN3,
    .seg_pins[SEGMENT_PIN3].direction = GPIO_DIRECTION_OUTPUT,
    .seg_pins[SEGMENT_PIN3].logic = GPIO_HIGH,

    .seg_type = SEG_COMMON_ANODE
};

keypad_t keypad1 = {
    .keypad_rows_pins[INDEX0].port = PORTA_INDEX,
    .keypad_rows_pins[INDEX0].pin_num = PIN7,
    .keypad_rows_pins[INDEX1].port = PORTB_INDEX,
    .keypad_rows_pins[INDEX1].pin_num = PIN0,
    .keypad_rows_pins[INDEX2].port = PORTB_INDEX,
    .keypad_rows_pins[INDEX2].pin_num = PIN2,
    .keypad_rows_pins[INDEX3].port = PORTB_INDEX,
    .keypad_rows_pins[INDEX3].pin_num = PIN3,

    .keypad_columns_pins[INDEX0].port = PORTB_INDEX,
    .keypad_columns_pins[INDEX0].pin_num = PIN1,
    .keypad_columns_pins[INDEX1].port = PORTB_INDEX,
    .keypad_columns_pins[INDEX1].pin_num = PIN5,
    .keypad_columns_pins[INDEX2].port = PORTB_INDEX,
    .keypad_columns_pins[INDEX2].pin_num = PIN6,
    .keypad_columns_pins[INDEX3].port = PORTB_INDEX,
    .keypad_columns_pins[INDEX3].pin_num = PIN7,

};


lcd_4bit_t lcd1 = {
    .lcd_rs.port = PORTD_INDEX,
    .lcd_rs.pin_num = PIN5,

    .lcd_en.port = PORTD_INDEX,
    .lcd_en.pin_num = PIN4,

    .lcd_data[INDEX0].port = PORTD_INDEX,
    .lcd_data[INDEX0].pin_num = PIN3,
    .lcd_data[INDEX1].port = PORTD_INDEX,
    .lcd_data[INDEX1].pin_num = PIN2,
    .lcd_data[INDEX2].port = PORTD_INDEX,
    .lcd_data[INDEX2].pin_num = PIN1,
    .lcd_data[INDEX3].port = PORTD_INDEX,
    .lcd_data[INDEX3].pin_num = PIN0,

};

volatile uint8_t count = 0;

void int0_app_handler(void) {
    count++;
}

void int1_app_handler(void) {
    count++;
}

void rb4_app_handler(void) {
    count++;
}

ext_interrupt_INTx_t int0 = {
    .EXT_InterruptHandler = int0_app_handler,
    .pin.port = PORTB_INDEX,
    .pin.pin_num = PIN0,
    .pin.direction = GPIO_DIRECTION_INPUT,
    .source = INTERRUPT_EXTERNAL_INT0,
    .edge = INTERRUPT_RISING_EDGE,
};

ext_interrupt_INTx_t int1 = {
    .EXT_InterruptHandler = int1_app_handler,
    .pin.port = PORTB_INDEX,
    .pin.pin_num = PIN1,
    .pin.direction = GPIO_DIRECTION_INPUT,
    .source = INTERRUPT_EXTERNAL_INT1,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_LOW_PRIORITY
};

ext_interrupt_RBx_t rb4 = {
    .EXT_InterruptHandler_HIGH = rb4_app_handler,
    .pin.port = PORTB_INDEX,
    .pin.pin_num = PIN4,
    .pin.direction = GPIO_DIRECTION_INPUT,
    .priority = INTERRUPT_LOW_PRIORITY
};

int main() {
    led_init(&led1);
    seven_seg_init(&seg1);

    seven_seg_write_number(&seg1, 3);

    keypad_init(&keypad1);

    lcd_4bit_init(&lcd1);


    lcd_4bit_send_char(&lcd1, 'A');

    lcd_4bit_send_char_pos(&lcd1, 'C', ROW1, 2);
    uint8 val = NO_KEY;
    
    volatile Std_ReturnType ret = E_OK;

    //    Interrupt_INTx_Init(&int0);
    //    Interrupt_INTx_Init(&int1);
    Interrupt_RBx_Init(&rb4);
    
    EEPROM_WriteByte(0x01,0x22);
    uint8 data;
    EEPROM_ReadByte(0x00, &data);
    for (;;) {
        led_turn_on(&led1);
        __delay_ms(1000);
        led_turn_off(&led1);
        __delay_ms(1000);
        ret = keypad_get_value(&keypad1, &val);
        if (NO_KEY != val) {
            for (int i = 0; i < 5; i++) {
                led_turn_on(&led1);
                __delay_ms(100);
                led_turn_off(&led1);
                __delay_ms(100);
            }
        }
        lcd_4bit_send_string_pos(&lcd1, "count is :", 1, 1);
        uint8 buff[4] = {0};
        convert_uint8_to_string(count, buff);
        lcd_4bit_send_string(&lcd1, buff);
        if (count)
            count--;

    }

    return (EXIT_SUCCESS);
}

