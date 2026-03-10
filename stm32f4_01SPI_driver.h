/*
 * stm32f4_01SPI_driver.h
 *
 *  Created on: Oct 4, 2025
 *      Author: MZH9PH
 */

#ifndef MY_INC_STM32F4_01SPI_DRIVER_H_
#define MY_INC_STM32F4_01SPI_DRIVER_H_

#define SPI_READY           0
#define SPI_BUSY_IN_RX      1
#define SPI_BUSY_IN_TX      2

// spi application state
#define SPI_Event_TX_CMPLT 1
#define SPI_Event_RX_CMPLT 2
#define SPI_Event_OVR_ERR  3
#define SPI_Event_CRC_ERR  4


#include "stm32_f401re.h"

/*
 * SPI Configuration Structure
 */
typedef struct
{
    uint8_t SPI_DeviceMode;         // Master or Slave
    uint8_t SPI_BusConfig;          // Full duplex / Half duplex / Simplex
    uint8_t SPI_SclkSpeed;          // Clock speed (baud rate prescaler)
    uint8_t SPI_DFF;                // Data frame format: 8-bit or 16-bit
    uint8_t SPI_CPOL;               // Clock polarity
    uint8_t SPI_CPHA;               // Clock phase
    uint8_t SPI_SSM;                // Software slave management (enable/disable)
} SPI_Config_t;


/*
 * SPI Handle Structure
 */
typedef struct
{
    SPI_RegDef_t *pSPIx;       // Pointer to SPI peripheral base address
    SPI_Config_t SPI_Config;   // SPI configuration settings

    uint8_t *pTxBuffer;      // Pointer to Tx buffer
    uint8_t *pRxBuffer;      // Pointer to Rx buffer
    uint32_t TxLen;          // Tx length
    uint32_t RxLen;          // Rx length
    uint8_t TxState;         // Transmission state
    uint8_t RxState;         // Reception state

} SPI_Handle_t;

/*
 * SPI Register Bit Position Definitions
 * (for SPI_CR1)
 */
#define SPI_CR1_CPHA       0
#define SPI_CR1_CPOL       1
#define SPI_CR1_MSTR       2
#define SPI_CR1_BR         3     // BR[2:0] spans bits 5:3
#define SPI_CR1_SPE        6
#define SPI_CR1_LSBFIRST   7
#define SPI_CR1_SSI        8
#define SPI_CR1_SSM        9
#define SPI_CR1_RXONLY     10
#define SPI_CR1_DFF        11
#define SPI_CR1_CRCNEXT    12
#define SPI_CR1_CRCEN      13
#define SPI_CR1_BIDIOE     14
#define SPI_CR1_BIDIMODE   15

/*
 * SPI Register Bit Position Definitions
 * (for SPI_CR2)
 */
#define SPI_CR2_RXDMAEN       0   // Rx buffer DMA enable
#define SPI_CR2_TXDMAEN       1   // Tx buffer DMA enable
#define SPI_CR2_SSOE          2   // SS output enable
#define SPI_CR2_FRF           4   // Frame format (TI mode)
#define SPI_CR2_ERRIE         5   // Error interrupt enable
#define SPI_CR2_RXNEIE        6   // RX buffer not empty interrupt enable
#define SPI_CR2_TXEIE         7   // TX buffer empty interrupt enable

/*
 * SPI Register Bit Position Definitions
 * (for SPI_SR)
 */
#define SPI_SR_RXNE        0   // Receive buffer not empty
#define SPI_SR_TXE         1   // Transmit buffer empty
#define SPI_SR_CHSIDE      2   // Channel side (used in I2S mode)
#define SPI_SR_UDR         3   // Underrun flag (I2S mode)
#define SPI_SR_CRCERR      4   // CRC error flag
#define SPI_SR_MODF        5   // Mode fault
#define SPI_SR_OVR         6   // Overrun flag
#define SPI_SR_BSY         7   // Busy flag
#define SPI_SR_FRE         8   // Frame format error (TI mode)


// The purpose of this macros is to reset the SPI peripheral in reset function

#define SPI1_REG_RESET()   do { (RCC->APB2RSTR |= (1 << 12)); (RCC->APB2RSTR &= ~(1 << 12)); } while(0)
#define SPI2_REG_RESET()   do { (RCC->APB1RSTR |= (1 << 14)); (RCC->APB1RSTR &= ~(1 << 14)); } while(0)
#define SPI3_REG_RESET()   do { (RCC->APB1RSTR |= (1 << 15)); (RCC->APB1RSTR &= ~(1 << 15)); } while(0)


/*
 * SPI Device Mode
 */
#define SPI_DEVICE_MODE_MASTER    1
#define SPI_DEVICE_MODE_SLAVE     0


/*
 * SPI Bus Configuration
 */
#define SPI_BUS_CONFIG_FD                 1   // Full Duplex
#define SPI_BUS_CONFIG_HD                 2   // Half Duplex
#define SPI_BUS_CONFIG_SIMPLEX_RXONLY     3   // Simplex Receive Only

/*
 * SPI Clock Speed (Baud Rate Prescaler)
 * These correspond to BR[2:0] bits in SPI_CR1
 */
#define SPI_SCLK_SPEED_DIV2       0
#define SPI_SCLK_SPEED_DIV4       1
#define SPI_SCLK_SPEED_DIV8       2
#define SPI_SCLK_SPEED_DIV16      3
#define SPI_SCLK_SPEED_DIV32      4
#define SPI_SCLK_SPEED_DIV64      5
#define SPI_SCLK_SPEED_DIV128     6
#define SPI_SCLK_SPEED_DIV256     7

/*
 * SPI Data Frame Format
 */
#define SPI_DFF_8BITS     0
#define SPI_DFF_16BITS    1

/*
 * SPI Clock Polarity (CPOL)
 */
#define SPI_CPOL_LOW      0
#define SPI_CPOL_HIGH     1

/*
 * SPI Clock Phase (CPHA)
 */
#define SPI_CPHA_LOW      0
#define SPI_CPHA_HIGH     1

/*
 * SPI Software Slave Management (SSM)
 */
#define SPI_SSM_DI        0
#define SPI_SSM_EN        1

/*
 * SPI related status flags definations
 */
#define SPI_TXE_FLAG	(1 << SPI_SR_TXE) // with this help i can check the register
#define SPI_RXNE_FLAG  (1 << SPI_SR_RXNE)  // RXNE is bit 0
#define SPI_BSY_FLAG   (1 << SPI_SR_BSY)   // BSY is bit 7

uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName);

// configuring SSI, If you enable SSM, then you must also set SSI to 1 to avoid a MODF (Mode Fault) error when you are the master.
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

// Enables or disables the peripheral clock for the given GPIO port
void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

// Initializes the SPI pin based on configuration
void SPI_Init(SPI_Handle_t *pSPIHandler);


// Resets the specified SPI port to its default state. we can reset all the gpio using RCC AHB1 reset peripheral.
void SPI_DeInit(SPI_RegDef_t *pSPIx);


// send and receive data SPI
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);

void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

// send and receive data SPI
uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandler, uint8_t *pTxBuffer, uint32_t Len);
uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandler, uint8_t *pRxBuffer, uint32_t Len);


// Enables or disables interrupt configuration for a spi pin= IRQ
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

// Handles the interrupt triggered by a GPIO pin
void SPI_IRQHandling(SPI_Handle_t *pHandle);

// It tells the microcontroller to actually start or stop SPI communication.
void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

//The SSOE bit (Slave Select Output Enable) is bit 2 of the SPI_CR2 register.it helps to control NSS
// it tells the MC When SPI is enabled, automatically pull NSS (PB12) LOW
void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi);

void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent);
void SPI_ClearOverFlag (SPI_RegDef_t *pSPIx);
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle);
void SPI_CloseReception(SPI_Handle_t *pSPIHandle);


#endif /* MY_INC_STM32F4_01SPI_DRIVER_H_ */
