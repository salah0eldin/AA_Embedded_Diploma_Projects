/* 
 * File:   spi.c
 * Author: Salah-Eldin
 *
 * Created on September 5, 2024
 */

//==================================================
// Includes
//==================================================
#include "spi.h"

//==================================================
// Statics
//==================================================
#if SPI_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
static void (*SPI_InterruptHandler)(void) = NULL;
#endif

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config);
static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations();
static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config);
 
//==================================================
// Function definitions
//==================================================
/**
 * @brief Initializes the SPI module based on the provided configuration.
 * 
 * This function configures the SPI module according to the specified configuration settings, 
 * enabling the appropriate pins and setting the communication parameters such as clock polarity, phase, 
 * and data order.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during the initialization.
 */
Std_ReturnType SPI_Init(const SPI_Config *Config){
    Std_ReturnType ret = E_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
        /* MSSP SPI Mode Select */
        SSPCON1bits.SSPM = Config->spi_mode;
        /* GPIO PIN Configurations */
        if((Config->spi_mode == SPI_MASTER_FOSC_DIV4) || (Config->spi_mode == SPI_MASTER_FOSC_DIV16) ||
            (Config->spi_mode == SPI_MASTER_FOSC_DIV64) || (Config->spi_mode == SPI_MASTER_FOSC_TMR2)){
            MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations();
        }
        else if((Config->spi_mode == SPI_SLAVE_SS_ENABLE) || (Config->spi_mode == SPI_SLAVE_SS_DISABLE)){
            MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(Config);
        }
        /* Clock Polarity Select */
        SSPCON1bits.CKP = Config->spi_config.ClockPolarity;
        /* SPI Sample Select */
        SSPSTATbits.SMP = Config->spi_config.SampleSelect;
        /* SPI Clock Select */
         SSPSTATbits.CKE = Config->spi_config.ClockSelect;
        /* MSSP SPI Interrupt Configurations*/
        MSSP_SPI_Interrupt_Init(Config);
        /* Enable SPI Module */
        SPI_ENABLE_MODULE();
    }
    
    return ret;
}

/**
 * @brief De-Initializes the SPI module.
 * 
 * This function disables the SPI module and releases any resources used.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during de-initialization.
 */
Std_ReturnType SPI_DeInit(const SPI_Config *Config){
    Std_ReturnType ret = E_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        /* Disable SPI Module */
        SPI_DISABLE_MODULE();
/* Interrupt Configurations */        
#if MSSP_SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
        MSSP_SPI_InterruptDisable();
#endif
    }
    return ret;
}

/**
 * @brief Sends a single byte of data via SPI.
 * 
 * This function transmits one byte of data using the SPI module as per the provided configuration.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data The byte of data to be transmitted.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during transmission.
 */
Std_ReturnType SPI_Master_Send_Receive_Byte(const SPI_Config *Config, const uint8 _dataT, uint8 *_dataR){
    Std_ReturnType ret = E_NOT_OK;
    
    if(NULL == Config){
        ret = E_NOT_OK;
    }
    else{
        SSPBUF = _dataT;
        while(!(SSPSTATbits.BF)); /* Waiting to transmit */
        *_dataR = SSPBUF;
    }
    
    return ret;
}

/**
 * @brief Receives a single byte of data via SPI.
 * 
 * This function reads one byte of data from the SPI module into the provided data pointer.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data A pointer to store the received byte.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during reception.
 */
Std_ReturnType SPI_Slave_Send_Receive_Byte(const SPI_Config *Config, const uint8 _dataT, uint8 *_dataR){
    Std_ReturnType ret = E_NOT_OK;
    
    if((NULL == Config) || (NULL == _dataR)){
        ret = E_NOT_OK;
    }
    else{
        *_dataR = SSPBUF;
        SSPBUF = _dataT;
    }
    
    return ret;
}

/**
 * @brief Sends a single byte of data via SPI in a non-blocking manner.
 * 
 * This function transmits one byte of data asynchronously, allowing the CPU to perform other tasks while the 
 * SPI transmission completes.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data The byte of data to be transmitted.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during transmission.
 */
Std_ReturnType SPI_Send_Byte_NonBlocking(const SPI_Config *Config, const uint8 _data){
    
}

/**
 * @brief Receives a single byte of data via SPI in a non-blocking manner.
 * 
 * This function reads one byte of data asynchronously from the SPI module into the provided data pointer.
 * 
 * @param Config A pointer to the SPI configuration structure (SPI_Config).
 * @param _data A pointer to store the received byte.
 * @return Std_ReturnType A status indicating the success or failure of the operation.
 *         - E_OK: The operation was successful.
 *         - E_NOT_OK: An error occurred during reception.
 */
Std_ReturnType SPI_Read_Byte_NonBlocking(const SPI_Config *Config, uint8 *_data){
    
}

//==================================================
// Statics definitions
//==================================================

static void MSSP_SPI_Interrupt_Init(const SPI_Config *Config){
/* Interrupt Configurations */        
#if SPI_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
    SPI_INTERRUPT_FLAG_CLEAR();
    SPI_INTERRUPT_ENABLE();
    SPI_InterruptHandler = Config->MSSP_SPI_InterruptHandler;
/* Interrupt Priority Configurations */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE 
    INTERRUPT_PriorityLevelsEnable();
    if(INTERRUPT_HIGH_PRIORITY == Config->priority){
        /* Enables all high-priority interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        MSSP_SPI_HighPrioritySet();
    }
    else if(INTERRUPT_LOW_PRIORITY == Config->priority){
        /* Enables all unmasked peripheral interrupts */
        INTERRUPT_GlobalInterruptHighEnable();
        INTERRUPT_GlobalInterruptLowEnable();
        MSSP_SPI_LowPrioritySet();
    }
    else{ /* Nothing */ }
#else
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
#endif      
#endif        
}

static void MSSP_SPI_Msster_Mode_GPIO_PIN_Configurations(){
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin_num = PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin_num = PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin_num = PIN3, .direction = GPIO_DIRECTION_OUTPUT};
    
    ret = gpio_pin_set_direction(&SPI_SDO); 
    ret = gpio_pin_set_direction(&SPI_SDI);
    ret = gpio_pin_set_direction(&SPI_CLK);
}

static void MSSP_SPI_Slave_Mode_GPIO_PIN_Configurations(const SPI_Config *Config){
    Std_ReturnType ret = E_NOT_OK;
    pin_config_t SPI_SDO = {.port = PORTC_INDEX, .pin_num = PIN5, .direction = GPIO_DIRECTION_OUTPUT};
    pin_config_t SPI_SDI = {.port = PORTC_INDEX, .pin_num = PIN4, .direction = GPIO_DIRECTION_INPUT};
    pin_config_t SPI_CLK = {.port = PORTC_INDEX, .pin_num = PIN3, .direction = GPIO_DIRECTION_INPUT};
    
    ret = gpio_pin_set_direction(&SPI_SDO); 
    ret = gpio_pin_set_direction(&SPI_SDI);
    ret = gpio_pin_set_direction(&SPI_CLK); 
    
    if(SPI_SLAVE_SS_ENABLE == Config->spi_mode){
        pin_config_t SPI_SS = {.port = PORTA_INDEX, .pin_num = PIN5, .direction = GPIO_DIRECTION_INPUT};
        ret = gpio_pin_set_direction(&SPI_SS);
    }
}

//==================================================
// ISR
//==================================================
/**
 * @brief MSSP SPI interrupt MCAL helper function
 */
void SPI_ISR(void)
{
#if SPI_INTERRUPT_ENABLE_FEATURE==INTERRUPT_FEATURE_ENABLE
    SPI_INTERRUPT_FLAG_CLEAR();
    if(SPI_InterruptHandler){
        SPI_InterruptHandler();
    }
#endif  
}