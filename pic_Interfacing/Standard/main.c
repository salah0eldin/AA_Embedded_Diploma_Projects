/* 
 * File:   main.c
 * Author: Salah-Eldin
 *
 * Created on August 10, 2024
 */

#include <stdio.h>
#include <stdlib.h>

#include "APP/application.h"
#include "MCAL_Layer/ADC/adc.h"
#include "MCAL_Layer/Timers/timer0.h"
#include "MCAL_Layer/Timers/timer1.h"
#include "MCAL_Layer/Timers/timer2.h"
#include "MCAL_Layer/CCP/ccp.h"
#include "MCAL_Layer/USART/usart.h"
#include "MCAL_Layer/SPI/spi.h"
#include "MCAL_Layer/I2C/I2C.h"

//void i2cint(void){
////    SSPBUF;
//}
//
//I2C_t i2c_obj = {
//    .I2C_InterruptHandler = i2cint,
//    .I2C_Interrupt_Write_Col = NULL,
//    .i2c_SMBus_control = I2C_SMBUS_DISABLE_CFG,
//    .i2c_mode = I2C_SLAVE_7BITS_ADD_S_P_ENABLED,
//    .i2c_slave_address = 0x10,
//    .i2c_slave_clk_stretching_control = I2C_SLAVE_CLK_STRETCING_DISABLE_CFG,
//    .i2c_slave_general_call_control = I2C_SLAVE_GENERAL_CALL_DISABLE_CFG,
//    .i2c_slew_rate = I2C_SLEW_RATE_ENABLE_CFG
//};

void int0int(void){
    TOG_BIT(LATC,0);
}

ext_interrupt_INTx_t int0_obj = {
  .EXT_InterruptHandler = int0int,
  .edge = INTERRUPT_FALLING_EDGE,
  .pin.port = PORTB_INDEX,
  .pin.pin_num = 0,
  .pin.direction = GPIO_DIRECTION_INPUT,
  .source = INTERRUPT_EXTERNAL_INT0
};

int main(){
    Interrupt_INTx_Init(&int0_obj);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
    CLR_BIT(TRISC,0);
    SET_BIT(TRISB, 6);
//    I2C_Slave_Init(&i2c_obj);
//    uint8_t data;
    for (;;) {
        if(READ_BIT(PORTB,6)){
            TOG_BIT(LATC,0);
            __delay_ms(500);
        }
    }

    return (EXIT_SUCCESS);
}

