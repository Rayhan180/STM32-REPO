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
