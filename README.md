// This header file contain header pin info for GPIO. I could not upload it in repo becuase of GM authentication.
/*
 * stm32f401xx_GPIO_drive.h
 *
 *  Created on: Aug 5, 2025
 *      Author: MZH9PH
 */
#include "stm32_f401re.h"
#ifndef MY_INC_STM32F401XX_GPIO_DRIVE_H_
#define MY_INC_STM32F401XX_GPIO_DRIVE_H_


/*
 * GPIO_PinConfig is a user-defined struct variable (of type GPIO_PinConfig_t)
 * that holds all the parameters needed to configure a GPIO pin, such as:
 */
typedef struct
{
    uint8_t GPIO_PinNumber;        // Pin number (0 to 15) 							/possible values from @GPIO_Pin_Numbers
    uint8_t GPIO_PinMode;          // Input, Output, Alt Function, Analog will use /possible values from @GPIO_Pin_Modes
    uint8_t GPIO_PinSpeed;         // Low, Medium, Fast, High 						/possible values from @GPIO_Output_Speed
    uint8_t GPIO_PinPuPdControl;   // Pull-up, Pull-down, No-pull					 /possible values from @GPIO_Pull_up_Pull_down
    uint8_t GPIO_PinOPType;        // Push-pull or Open-drain 						/possible values from @Push_Pull_open_drain
    uint8_t GPIO_PinAltFunMode;    // Alternate function mode						 /possible values from
} GPIO_PinConfig_t;

typedef struct
{
    GPIO_RegDef_t *pGPIOx;           // Base address of the GPIO port (e.g., GPIOA)
    GPIO_PinConfig_t GPIO_PinConfig; // GPIO pin configuration settings
} GPIO_Handle_t;


/*
 * GPIO Alternate Function numbers (AF[0:15])
 * These are generic names — actual meaning depends on the MCU datasheet.
 */
#define GPIO_AF0_SYSTEM        0x0U  /* System: RTC, WKUP, MCO, etc. */
#define GPIO_AF1_TIM1_TIM2     0x1U  /* TIM1, TIM2                    */
#define GPIO_AF2_TIM3_TIM5     0x2U  /* TIM3, TIM4, TIM5               */
#define GPIO_AF3_TIM8_TIM11    0x3U  /* TIM8, TIM9, TIM10, TIM11       */
#define GPIO_AF4_I2C1_I2C3     0x4U  /* I2C1, I2C2, I2C3               */
#define GPIO_AF5_SPI1_SPI4     0x5U  /* SPI1, SPI2, SPI4               */
#define GPIO_AF6_SPI3          0x6U  /* SPI3                           */
#define GPIO_AF7_USART1_3      0x7U  /* USART1, USART2, USART3         */
#define GPIO_AF8_USART4_6      0x8U  /* USART4, USART5, USART6         */
#define GPIO_AF9_CAN1_CAN2     0x9U  /* CAN1, CAN2, TIM12–14           */
#define GPIO_AF10_OTG_FS_HS    0xAU  /* USB OTG FS / HS                */
#define GPIO_AF11_ETH          0xBU  /* Ethernet                       */
#define GPIO_AF12_FSMC_SDIO    0xCU  /* FSMC, SDIO, OTG HS              */
#define GPIO_AF13_DCMI         0xDU  /* DCMI / Camera                   */
#define GPIO_AF14_LTDC         0xEU  /* LCD-TFT Display Controller      */
#define GPIO_AF15_EVENTOUT     0xFU  /* EVENTOUT                        */

/*
 * @GPIO_Pin_Numbers
 */
#define GPIO_PIN_0             0U
#define GPIO_PIN_1             1U
#define GPIO_PIN_2             2U
#define GPIO_PIN_3             3U
#define GPIO_PIN_4             4U
#define GPIO_PIN_5             5U
#define GPIO_PIN_6             6U
#define GPIO_PIN_7             7U
#define GPIO_PIN_8             8U
#define GPIO_PIN_9             9U
#define GPIO_PIN_10            10U
#define GPIO_PIN_11            11U
#define GPIO_PIN_12            12U
#define GPIO_PIN_13            13U
#define GPIO_PIN_14            14U
#define GPIO_PIN_15            15U

/*
 * GPIO PIn possible modes/////////////////////////////////////////////
 */

/* @GPIO_Pin_Modes */
#define GPIO_MODE_IN           0x0U  /* Input mode */
#define GPIO_MODE_OUT          0x1U  /* Output mode */
#define GPIO_MODE_ALTFN        0x2U  /* Alternate function mode */
#define GPIO_MODE_ANALOG       0x3U  /* Analog mode */
/* GPIO Interrupt Modes (EXTI) */
#define GPIO_MODE_IT_FT        0x4U  /* Interrupt mode: Falling edge trigger */
#define GPIO_MODE_IT_RT        0x5U  /* Interrupt mode: Rising edge trigger */
#define GPIO_MODE_IT_RFT       0x6U  /* Interrupt mode: Rising + Falling edge trigger */

/*
 * GPIO Output Types (OTYPER register)
 */

/* @Push_Pull_open_drain (default) */
#define GPIO_OP_TYPE_PP        0x0U
/* Open-Drain */
#define GPIO_OP_TYPE_OD        0x1U
/*
 * @GPIO_Output_Speed (OSPEEDR, 2 bits per pin)
 * Note: Names can vary by family (Medium/Fast/High). These values match F4/F7/H7 style.
 */
#define GPIO_SPEED_LOW         0x0U  /* ~2 MHz (lowest slew)   */
#define GPIO_SPEED_MEDIUM      0x1U  /* ~25 MHz                */
#define GPIO_SPEED_FAST        0x2U  /* ~50 MHz                */
#define GPIO_SPEED_HIGH        0x3U  /* ~100 MHz (highest slew)*/

/*
 * @GPIO_Pull_up_Pull_down (PUPDR, 2 bits per pin)
 */
#define GPIO_NO_PUPD           0x0U  /* Floating               */
#define GPIO_PIN_PU            0x1U  /* Pull-Up                */
#define GPIO_PIN_PD            0x2U  /* Pull-Down              */
/* 0x3U is reserved in many families */


/*
 * GPIO driver function names/////////////////////////////////////////////
 */

// Enables or disables the peripheral clock for the given GPIO port
void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi);


// Initializes the GPIO pin based on configuration
void GPIO_Init(GPIO_Handle_t *pGPIOHandler);


// Resets the specified GPIO port to its default state. we can reset all the gpio using RCC AHB1 reset peripheral.
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// Reads the value from a specific input pin (placeholder format)
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber); // it should return 0 or 1. can use Boolean or uint 8.

// Write the value from a specific input pin (placeholder format)
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx); // here it is 16 bit port.

// Reads the value from a specific Outputt pin (placeholder format)
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value); // it should return 0 or 1. can use Boolean or uint 8.

// Writes a value (HIGH or LOW) to a specific output pin
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value); // here it is 16 bit port. This can take Pin set or reset value.

// Toggles the current state of an output pin
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx,  uint8_t PinNumber);

// Enables or disables interrupt configuration for a GPIO pin= IRQ
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);

// Handles the interrupt triggered by a GPIO pin
void GPIO_IRQHandling(uint8_t PinNumber);



#endif /* MY_INC_STM32F401XX_GPIO_DRIVE_H_ */



///////////////// Here is .C file for SPI

/*
 * stm32f4_01SPI_driver.c
 *
 *  Created on: Oct 4, 2025
 *      Author: MZH9PH
 */

#include"stm32f4_01SPI_driver.h"
#include "stm32_f401re.h"

static void spi_txe_interrupt_handle (SPI_Handle_t *pSPIHandle);
static void spi_rxne_interrupt_handle (SPI_Handle_t *pSPIHandle);
static void spi_ovr_err_interrupt_handle (SPI_Handle_t *pSPIHandle);



void SPI_IRQHandling(SPI_Handle_t *pSPIHandle)
{
	uint8_t temp1, temp2;

	//firs tlets check txe
	temp1 = pSPIHandle->pSPIx->SR & (1<< SPI_SR_TXE);
	temp2 = pSPIHandle->pSPIx->SR & (1<< SPI_CR2_TXEIE);

	if (temp1 && temp2)
	{
		// handle txe
		spi_txe_interrupt_handle(pSPIHandle);
	}

	// now check for rxne

	temp1 = pSPIHandle->pSPIx->SR & (1<< SPI_SR_RXNE);
	temp2 = pSPIHandle->pSPIx->SR & (1<< SPI_CR2_RXNEIE);

	if (temp1 && temp2)
	{
		// handle txe
		spi_rxne_interrupt_handle(pSPIHandle);
	}

	// check for ovr

	temp1 = pSPIHandle->pSPIx->SR & (1<< SPI_SR_OVR);
	temp2 = pSPIHandle->pSPIx->SR & (1<< SPI_CR2_ERRIE);

	if (temp1 && temp2)
	{
		// handle txe
		spi_ovr_err_interrupt_handle(pSPIHandle);
	}

}


//This function enables or disables SPI interrupts in the NVIC (Nested Vectored Interrupt Controller).
void SPI_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
    if (EnorDi == ENABLE)
    {
        // 1. Enable interrupt in NVIC ISER (Interrupt Set-Enable Register)
        if (IRQNumber <= 31)
        {
            *NVIC_ISER0 |= (1 << IRQNumber);  // ISER0 handles IRQ 0–31
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ISER1 |= (1 << (IRQNumber % 32)); // ISER1 handles IRQ 32–63
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ISER2 |= (1 << (IRQNumber % 64)); // ISER2 handles IRQ 64–95
        }
    }
    else
    {
        // 2. Disable interrupt in NVIC ICER (Interrupt Clear-Enable Register)
        if (IRQNumber <= 31)
        {
            *NVIC_ICER0 |= (1 << IRQNumber);  // ICER0 disables IRQ 0–31
        }
        else if (IRQNumber > 31 && IRQNumber < 64)
        {
            *NVIC_ICER1 |= (1 << (IRQNumber % 32)); // ICER1 disables IRQ 32–63
        }
        else if (IRQNumber >= 64 && IRQNumber < 96)
        {
            *NVIC_ICER2 |= (1 << (IRQNumber % 64)); // ICER2 disables IRQ 64–95
        }
    }
}

//This sets the priority level of a specific SPI interrupt.
//Each interrupt gets a 4-bit priority field in the NVIC’s IPR registers.

void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority)
{
    // 1. Find the IPR register (each holds 4 priority fields)
    uint8_t iprx = IRQNumber / 4;
    uint8_t iprx_section = IRQNumber % 4;

    uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTATED);

    *(NVIC_IPR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}




/******************** Peripheral Clock Control ********************/
void SPI_PeripheralClockControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if (EnOrDi == ENABLE)
    {
        if (pSPIx == SPI1)
        {
        	RCC_SPI1_CLK_ENABLE();
        }
        else if (pSPIx == SPI2)
        {
        	RCC_SPI2_CLK_ENABLE();
        }
        else if (pSPIx == SPI3)
        {
        	RCC_SPI3_CLK_ENABLE();
        }
    }
    else
    {
    	//do nothing
    }
}

/*
 * Function: SPI_Init
 * To configure and initialize an SPI peripheral (like SPI1, SPI2) based on user-defined settings stored in a handle.
 * for example Before calling SPI_Init(), in my SPI2_Inits() function, i do:
 * SPI2Handle.pSPIx = SPI2;  // SPI2 peripheral base address
 * SPI2Handle.SPI_Config.SPI_DeviceMode = SPI_DEVICE_MODE_MASTER; // = 1
 * then i call at the end SPI_Init(&SPI2Handle);
 * Which sets the bit 2 in CR1.
*/
void SPI_Init(SPI_Handle_t *pSPIHandle)
{
    uint32_t tempreg = 0;

    // 1. Enable the peripheral clock
    SPI_PeripheralClockControl(pSPIHandle->pSPIx, ENABLE);

      // 2. Device Mode
      tempreg |= pSPIHandle->SPI_Config.SPI_DeviceMode << SPI_CR1_MSTR;

      // 3. Bus Configuration
      if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_FD)
      {
          // Full Duplex
          tempreg &= ~(1 << SPI_CR1_BIDIMODE);
      }
      else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_HD)
      {
          // Half Duplex
          tempreg |= (1 << SPI_CR1_BIDIMODE);
      }
      else if (pSPIHandle->SPI_Config.SPI_BusConfig == SPI_BUS_CONFIG_SIMPLEX_RXONLY)
      {
          // Simplex receive only
          tempreg &= ~(1 << SPI_CR1_BIDIMODE);
          tempreg |= (1 << SPI_CR1_RXONLY);
      }

      // 4. Clock Speed
      tempreg |= (pSPIHandle->SPI_Config.SPI_SclkSpeed << SPI_CR1_BR);

      // 5. Data Frame Format
      tempreg |= (pSPIHandle->SPI_Config.SPI_DFF << SPI_CR1_DFF);

      // 6. Clock Polarity
      tempreg |= (pSPIHandle->SPI_Config.SPI_CPOL << SPI_CR1_CPOL);

      // 7. Clock Phase
      tempreg |= (pSPIHandle->SPI_Config.SPI_CPHA << SPI_CR1_CPHA);

      // 8. Software Slave Management
      tempreg |= (pSPIHandle->SPI_Config.SPI_SSM << SPI_CR1_SSM);

      // 9. Write to CR1
      pSPIHandle->pSPIx->CR1 = tempreg;

      // 10. If SSM enabled, set SSI to avoid MODF error
      if (pSPIHandle->SPI_Config.SPI_SSM)
      {
    	  pSPIHandle->pSPIx->CR1 |= (1 << SPI_CR1_SSI);
      }
}



void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
    if(pSPIx == SPI1)
    {
        SPI1_REG_RESET();
    }
    else if(pSPIx == SPI2)
    {
        SPI2_REG_RESET();
    }
    else if(pSPIx == SPI3)
    {
        SPI3_REG_RESET();
    }

}

/******************** SPI Data Send and Receive ********************/
//this is blocking call

void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len)
{
	while (Len > 0)
	{
        // Wait until TXE flag is set
        while (SPI_GetFlagStatus(pSPIx, SPI_TXE_FLAG) == FLAG_RESET); // if tx is 0 we can proceed

        if ((pSPIx ->CR1 & (1 << SPI_CR1_DFF))) // dff = data frame format
        		{
        	// 16 BIT DFF
        	// LOAD THE DATA INTO DR
        	pSPIx -> DR = *((uint16_t*) pTxBuffer);
        	Len--;
        	Len--;
        	pTxBuffer+= 2;

        		}
        else
        	{
        	// 8 bit dff
        	pSPIx -> DR = *pTxBuffer;
        	Len--;
        	pTxBuffer++;

        	}
	}

}
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len){

	while (Len > 0)
		{
	        // Wait until RXNE flag is set
	        while (SPI_GetFlagStatus(pSPIx, SPI_RXNE_FLAG) == FLAG_RESET); // if rxne is 1 we can proceed

	        if ((pSPIx ->CR1 & (1 << SPI_CR1_DFF)))
	        		{
	        	// 16 BIT DFF
	        	// read THE DATA from  DR to ex
	        	*((uint16_t*) pRxBuffer) = pSPIx -> DR;
	        	Len--;
	        	Len--;
	        	pRxBuffer+= 2;

	        		}
	        else
	        	{
	        	// 8 bit dff
	        	*pRxBuffer = pSPIx -> DR;
	        	Len--;
	        	pRxBuffer++;

	            }


		}


}

uint8_t SPI_SendDataIT(SPI_Handle_t *pSPIHandler, uint8_t *pTxBuffer, uint32_t Len)
{

	uint8_t state = pSPIHandler->TxState;
	if (state != SPI_BUSY_IN_TX)
	{
	pSPIHandler->pTxBuffer = pTxBuffer;
	pSPIHandler->TxLen = Len;
	pSPIHandler->TxState = SPI_BUSY_IN_TX;
	pSPIHandler->pSPIx->CR2 |= (1 << SPI_CR2_TXEIE);
	}
	return state;
}

uint8_t SPI_ReceiveDataIT(SPI_Handle_t *pSPIHandler, uint8_t *pRxBuffer, uint32_t Len)
{

	uint8_t state = pSPIHandler->RxState;
	if (state != SPI_BUSY_IN_RX)
	{
	pSPIHandler->pRxBuffer = pRxBuffer;
	pSPIHandler->RxLen = Len;
	pSPIHandler->RxState = SPI_BUSY_IN_RX;
	pSPIHandler->pSPIx->CR2 |= (1 << SPI_CR2_RXNEIE);
	}
	return state;
}

/******************** Peripheral Control ********************/

void SPI_PeripheralControl(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SPE);   // Enable SPI
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SPE);  // Disable SPI
    }
}

// You must set SSI = 1 to keep the SPI in master mode.
void SPI_SSIConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi)
{
    if(EnOrDi == ENABLE)
    {
        pSPIx->CR1 |= (1 << SPI_CR1_SSI);   // Set SSI bit
    }
    else
    {
        pSPIx->CR1 &= ~(1 << SPI_CR1_SSI);  // Clear SSI bit
    }
}


void SPI_SSOEConfig(SPI_RegDef_t *pSPIx, uint8_t EnOrDi) //The SSOE bit (Slave Select Output Enable) is bit 2 of the SPI_CR2 register.
{
    if (EnOrDi == ENABLE)
    {
        pSPIx->CR2 |= (1 << SPI_CR2_SSOE);
    }
    else
    {
        pSPIx->CR2 &= ~(1 << SPI_CR2_SSOE);
    }
}
/******************** Status Flag Helpers ********************/
uint8_t SPI_GetFlagStatus(SPI_RegDef_t *pSPIx, uint32_t FlagName)  // if 0 tx is clear ready to take new, if 1 can not go means it is in work.
{
    if (pSPIx->SR & FlagName)
    {
        return FLAG_SET;
    }
	return FLAG_RESET;
}


// helper function implementation

// TXE (Transmit Buffer Empty) Interrupt Handler
static void spi_txe_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
    // Check if Data Frame Format = 16 bits
    if (pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
    {
        // 16-bit DFF
        pSPIHandle->pSPIx->DR = *((uint16_t*)pSPIHandle->pTxBuffer);
        pSPIHandle->TxLen -= 2;  // Two bytes sent
        (uint16_t*)pSPIHandle->pTxBuffer++;  // Advance pointer by 2 bytes
    }
    else
    {
        // 8-bit DFF
        pSPIHandle->pSPIx->DR = *pSPIHandle->pTxBuffer;
        pSPIHandle->TxLen--;
        pSPIHandle->pTxBuffer++;
    }

    // Transmission complete
    if (!pSPIHandle->TxLen)
    {
        // Disable TXE interrupt
        pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);

        // Reset transmission fields
        pSPIHandle->pTxBuffer = NULL;
        pSPIHandle->TxLen = 0;
        pSPIHandle->TxState = SPI_READY;

        // Notify application
        SPI_ApplicationEventCallback(pSPIHandle, SPI_Event_TX_CMPLT);
    }
}

static void spi_rxne_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
    // Check if Data Frame Format = 16 bits
    if (pSPIHandle->pSPIx->CR1 & (1 << SPI_CR1_DFF))
    {
        // 16-bit DFF
        *((uint16_t*)pSPIHandle->pRxBuffer) = pSPIHandle->pSPIx->DR;
        pSPIHandle->RxLen -= 2;
        (uint16_t*)pSPIHandle->pRxBuffer++;
    }
    else
    {
        // 8-bit DFF
        *pSPIHandle->pRxBuffer = pSPIHandle->pSPIx->DR;
        pSPIHandle->RxLen--;
        pSPIHandle->pRxBuffer++;
    }

    // Reception complete
    if (!pSPIHandle->RxLen)
    {
        // Disable RXNE interrupt
        pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);

        // Reset reception fields
        pSPIHandle->pRxBuffer = NULL;
        pSPIHandle->RxLen = 0;
        pSPIHandle->RxState = SPI_READY;

        // Notify application
        SPI_ApplicationEventCallback(pSPIHandle, SPI_Event_RX_CMPLT);
    }
}

static void spi_ovr_err_interrupt_handle(SPI_Handle_t *pSPIHandle)
{
    uint8_t temp;

    // Clear OVR flag only if SPI is not busy in transmission
    if (pSPIHandle->TxState != SPI_BUSY_IN_TX)
    {
        temp = pSPIHandle->pSPIx->DR; // Read DR
        temp = pSPIHandle->pSPIx->SR; // Read SR
        (void)temp;                   // Dummy read to clear OVR flag
    }

    // Notify application about the error
    SPI_ApplicationEventCallback(pSPIHandle, SPI_Event_OVR_ERR);
}


void SPI_ApplicationEventCallback(SPI_Handle_t *pSPIHandle, uint8_t AppEvent)
{
    switch(AppEvent)
    {
        case SPI_Event_TX_CMPLT:
            //printf("SPI Transmission Complete\n");
            break;

        case SPI_Event_RX_CMPLT:
            //printf("SPI Reception Complete\n");
            break;

        case SPI_Event_OVR_ERR:
            //printf("SPI Overrun Error!\n");
            break;

        default:
            break;
    }
}

void SPI_ClearOverFlag (SPI_RegDef_t *pSPIx)
{
    // Read DR and SR to clear the OVR flag
    uint8_t temp;
    temp = pSPIx->DR;
    temp = pSPIx->SR;
    (void)temp;  // avoid compiler warning
}
void SPI_CloseReception(SPI_Handle_t *pSPIHandle)
{
    // Disable RXNE interrupt
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_RXNEIE);

    // Reset reception fields
    pSPIHandle->pRxBuffer = NULL;
    pSPIHandle->RxLen = 0;
    pSPIHandle->RxState = SPI_READY;
}
void SPI_CloseTransmission(SPI_Handle_t *pSPIHandle)
{
    // Disable TXE interrupt
    pSPIHandle->pSPIx->CR2 &= ~(1 << SPI_CR2_TXEIE);

    // Reset transmission fields
    pSPIHandle->pTxBuffer = NULL;
    pSPIHandle->TxLen = 0;
    pSPIHandle->TxState = SPI_READY;
}



