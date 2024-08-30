/* 
 * File:   main.c
 * Author: Salah-Eldin
 *
 * Created on August 10, 2024, 10:32 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include "APP/application.h"
#include "MCAL_Layer/ADC/adc.h"
#include "MCAL_Layer/Timers/timer0.h"
#include "MCAL_Layer/Timers/timer1.h"

led_t led1 = {
    .port = PORTA_INDEX,
    .pin = PIN1,
    .connection = LED_POSITIVE,
    .led_status = LED_ON
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

adc_config_t adc1 = {
    .acq_time = ADC_12_TAD,
    .clock = ADC_CLOCK_FOSC_DIV_16,
    .channel = ADC_CHANNEL_AN0,
    .res_format = ADC_RESULT_RIGHT,
    .volt_P_reference = ADC_VOLT_REF_DISABLE,
    .volt_N_reference = ADC_VOLT_REF_DISABLE
};

void timer0_int(void){
    led_toggle(&led1);
}

timer0_t timer0_obj = {
  .TIMR0_InterruptHandler = timer0_int,
  .mode = TIMER0_TIMER_MODE,
  .preload = 3036,
  .prescaler_status = TIMER0_PRESCALER_ENABLE_CFG,
  .prescaler_val = TIMER0_PRESCALER_DIV_8,
  .reg_size = TIMER0_16BIT_REGISTER_MODE
};

void timer1_int(void){
    led_toggle(&led1);
}

timer1_t timer1_obj = {
  .TIMR1_InterruptHandler = timer1_int,
  .mode = TIMER1_TIMER_MODE_CFG,
  .preload = 15536,
  .prescaler = TIMER1_PRESCALER_DIV_2,
  .osc_enable = TIMER1_OSC_DISABLE_CFG,
  .rw_mode = TIMER1_16BITS_RW_MODE_CFG
};

int main() {
    led_init(&led1);
 
    lcd_4bit_init(&lcd1);

    lcd_4bit_send_char(&lcd1, 'A');

    lcd_4bit_send_char_pos(&lcd1, 'C', ROW1, 2);
    
    ADC_AN_DIG_PORT_CONFIG(ADC_TIL_AN0);
    ADC_Init(&adc1);

    uint16 adc_res = 0;
    
//    Timer0_Init(&timer0_obj);
    Timer1_Init(&timer1_obj);
    
    volatile Std_ReturnType ret = E_OK;
    
    for (;;) {
//        led_turn_on(&led1);
//        __delay_ms(100);
//        led_turn_off(&led1);
//        __delay_ms(100);
        ADC_Get_Conversion_Blocking(&adc1,ADC_CHANNEL_AN0,&adc_res);
        uint8 buff[6] = {0};
        convert_uint16_to_string(adc_res,buff);
        lcd_4bit_send_string_pos(&lcd1,buff,1,1);
        lcd_4bit_send_string(&lcd1,"     ");
    }

    return (EXIT_SUCCESS);
}

