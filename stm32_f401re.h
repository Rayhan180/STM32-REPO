/*
 * stm32_f401re.h
 *
 *  Created on: Jul 27, 2025
 *      Author: MZH9PH
 */
/* RH- will be defining the  */

#ifndef MY_INC_STM32_F401RE_H_
#define MY_INC_STM32_F401RE_H_

#include<stddef.h>
#include<stdint.h>
#define __vo volatile		//WHY WE USE VOLATILE?

#define NO_PR_BITS_IMPLEMENTATED		4
#define NVIC_IPR_BASE_ADDR ((__vo uint32_t*)0xE000E400) // Base address of NVIC IPR

// NVIC ISER (Interrupt Set-Enable Registers)
#define NVIC_ISER0   ((__vo uint32_t*)0xE000E100)   // IRQ 0-31
#define NVIC_ISER1   ((__vo uint32_t*)0xE000E104)   // IRQ 32-63
#define NVIC_ISER2   ((__vo uint32_t*)0xE000E108)   // IRQ 64-95
#define NVIC_ISER3   ((__vo uint32_t*)0xE000E10c)   // IRQ

// NVIC ICER (Interrupt Clear-Enable Registers)
#define NVIC_ICER0   ((__vo uint32_t*)0xE000E180)   // IRQ 0-31
#define NVIC_ICER1   ((__vo uint32_t*)0xE000E184)   // IRQ 32-63
#define NVIC_ICER2   ((__vo uint32_t*)0xE000E188)   // IRQ 64-95
#define NVIC_ICER3   ((__vo uint32_t*)0xE000E18c)   // IRQ

/* RH- will be defining the base, rom and flash MEMORY BASE address.
 *
 */
#define FLASH_BASEADDR			0x08000000U
#define SRAM1_BASEADDR			0x20000000U 	//112 KB
#define SRAM2_BASEADDR			0x2001C000U 	//16 KB
#define OTP_AREA_BASEADDR		0x1FFF7800U
#define SYSTEM_MEM_BASEADDR		0x1FFF0000U  	//ROM AREA START
#define SRAM					SRAM1_BASEADD


/* RH- will be defining the APB1 APB2, AHB1, AHB2 BASE address.  */

#define PERIPH_BASEADDR			0X40000000U

#define APB1PERIPH_BASEADDR		PERIPH_BASEADDR
#define APB2PERIPH_BASEADDR		0x40010000
#define AHB1PERIPH_BASEADDR		0x40020000
#define AHB2PERIPH_BASEADDR		0x50000000

/* RH- will be defining the BASE ADD of AHB1 BUS PERIPHERALS F.E(GPOA,B,C,D,E,F,G,I) */
#define GPIOA_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0000)
#define GPIOB_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0400)
#define GPIOC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0800)
#define GPIOD_BASEADDR			(AHB1PERIPH_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1000)
#define GPIOF_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1400)
#define GPIOG_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1800)
#define GPIOH_BASEADDR			(AHB1PERIPH_BASEADDR + 0x1C00)
#define GPIOI_BASEADDR			(AHB1PERIPH_BASEADDR + 0x2000)

#define RCC_BASEADDR			(AHB1PERIPH_BASEADDR + 0x3800)

/* RH- will be defining the BASE ADD of APB1 NECESSARY BUS PERIPHERALS  */
#define TIM2_BASEADDR			(APB1PERIPH_BASEADDR + 0x0000)
#define TIM3_BASEADDR			(APB1PERIPH_BASEADDR + 0x0400)
#define TIM4_BASEADDR			(APB1PERIPH_BASEADDR + 0x0800)
#define TIM5_BASEADDR			(APB1PERIPH_BASEADDR + 0x0C00)
#define TIM6_BASEADDR			(APB1PERIPH_BASEADDR + 0x1000)

#define WWDG_BASEADDR			(APB1PERIPH_BASEADDR + 0x2C00)

#define IWDG_BASEADDR			(APB1PERIPH_BASEADDR + 0x3000)

#define SPI2_I2S2_BASEADDR		(APB1PERIPH_BASEADDR + 0x3800)
#define SPI3_I2S3_BASEADDR		(APB1PERIPH_BASEADDR + 0x3C00)

#define USART2_BASEADDR			(APB1PERIPH_BASEADDR + 0x4400)
#define USART3_BASEADDR			(APB1PERIPH_BASEADDR + 0x4800)

#define I2C1_BASEADDRE			(APB1PERIPH_BASEADDR + 0x5400)
#define I2C2_BASEADDR			(APB1PERIPH_BASEADDR + 0x5800)
#define I2C3_BASEADDR			(APB1PERIPH_BASEADDR + 0x5C00)

#define CAN1_BASEADDR			(APB1PERIPH_BASEADDR + 0x6400)
#define PWR_BASEADDR			(APB1PERIPH_BASEADDR + 0x7000)
#define DAC_BASEADDR			(APB1PERIPH_BASEADDR + 0x7400)

/* RH- will be defining the BASE ADD of APB2 NECESSARY BUS PERIPHERALS  */
#define TIM1_BASEADDR			(APB2PERIPH_BASEADDR + 0x0000)
#define TIM8_BASEADDR			(APB2PERIPH_BASEADDR + 0x0400)

#define USART1_BASEADDR			(APB2PERIPH_BASEADDR + 0x1000)
#define USART6_BASEADDR			(APB2PERIPH_BASEADDR + 0x1400)

#define ADC1_2_3_BASEADDR		(APB2PERIPH_BASEADDR + 0x2000)
#define SDIO_BASEADDR			(APB2PERIPH_BASEADDR + 0x2C00)

#define SPI1_BASEADDR			(APB2PERIPH_BASEADDR + 0x3000)

#define EXTI_BASEADDR			(APB2PERIPH_BASEADDR + 0x3C00)  // USED FOR INTERRUPT
#define SYSCFG_BASE_ADDR		(APB2PERIPH_BASEADDR + 0x3800)



/******************** IRQ (Interrupt Request) Numbers ********************/

#define IRQ_NO_EXTI0        6
#define IRQ_NO_EXTI1        7
#define IRQ_NO_EXTI2        8
#define IRQ_NO_EXTI3        9
#define IRQ_NO_EXTI4        10
#define IRQ_NO_EXTI9_5      23
#define IRQ_NO_EXTI15_10    40

// for SPI
#define IRQ_NO_SPI1       35
#define IRQ_NO_SPI2       36
#define IRQ_NO_SPI3       51

// NVIC IRQ Priority Levels (0 = highest, 15 = lowest)
#define NVIC_IRQ_PRIORITY0     0
#define NVIC_IRQ_PRIORITY1     1
#define NVIC_IRQ_PRIORITY2     2
#define NVIC_IRQ_PRIORITY3     3
#define NVIC_IRQ_PRIORITY4     4
#define NVIC_IRQ_PRIORITY5     5
#define NVIC_IRQ_PRIORITY6     6
#define NVIC_IRQ_PRIORITY7     7
#define NVIC_IRQ_PRIORITY8     8
#define NVIC_IRQ_PRIORITY9     9
#define NVIC_IRQ_PRIORITY10    10
#define NVIC_IRQ_PRIORITY11    11
#define NVIC_IRQ_PRIORITY12    12
#define NVIC_IRQ_PRIORITY13    13
#define NVIC_IRQ_PRIORITY14    14
#define NVIC_IRQ_PRIORITY15    15



// Macro to convert GPIO port base address to corresponding port code
#define GPIO_BASEADDR_TO_CODE(x)  ((x) == GPIOA ? 0 : \
                                   (x) == GPIOB ? 1 : \
                                   (x) == GPIOC ? 2 : \
                                   (x) == GPIOD ? 3 : \
                                   (x) == GPIOE ? 4 : \
                                   (x) == GPIOF ? 5 : \
                                   (x) == GPIOG ? 6 : \
                                   (x) == GPIOH ? 7 : 0)


/* NOW ADDRESS OF THE PERIPHERALS REGISTER. Start with GPIOA. LATER WE WILL MAK EFOR SPI,UART,I2C */

typedef struct // this is generic structure for all gpio port.
{
	__vo uint32_t MODER;	// ADDRESS OFFSET OF THSI 0X00
	__vo uint32_t OTYPER;	// 0X04
	__vo uint32_t OSPEED;	//0x08
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFRL;
	__vo uint32_t AFR[2];	//HERE WE MAKE ARROW OF 2 REG. AS HIGH AND LOW. SO AFR[0]0 WILL BE LOW AND HIGH WILL BE 1
} GPIO_RegDef_t;

/* SPI register definition structure */
typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SR;
    volatile uint32_t DR;
    volatile uint32_t CRCPR;
    volatile uint32_t RXCRCR;
    volatile uint32_t TXCRCR;
    volatile uint32_t I2SCFGR;
    volatile uint32_t I2SPR;
} SPI_RegDef_t;

/* HOW to use this structure?
 * GPIO_RegDef_t *pGPIOA = (GPIO_RegDef_t*)0x40020000;
 * instead of writing (GPIO_RegDef_t*)0x40020000, i can directly call GPIOA
 */

#define GPIOA ((GPIO_RegDef_t*) GPIOA_BASEADDR)		//Here i am type casting (making it as pointer) the address GPIOA_BASEADDR
#define GPIOB ((GPIO_RegDef_t*) GPIOB_BASEADDR)		//"Compiler, treat this address as a pointer to a GPIO_RegDef_t structure."
#define GPIOC ((GPIO_RegDef_t*) GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t*) GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t*) GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t*) GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t*) GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t*) GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t*) GPIOI_BASEADDR)


// SPIx define
#define SPI1   ((SPI_RegDef_t *)SPI1_BASEADDR)
#define SPI2   ((SPI_RegDef_t *)SPI2_I2S2_BASEADDR)
#define SPI3   ((SPI_RegDef_t *)SPI3_I2S3_BASEADDR)


#define EXTI  ((EXTI_RegDef_t*) EXTI_BASEADDR)
//#define EXTI  ((GPIO_RegDef_t*) EXTI_BASEADDR)

#define RCC ((RCC_RegDef_t*) RCC_BASEADDR)

#define SYSCFG ((SYSCFG_RegDef_t *)SYSCFG_BASE_ADDR)

#define SYSCFG_PCLK_EN()  (RCC->APB2ENR |= (1 << 14))




typedef struct
{
	__vo uint32_t MEMRMP;       // Memory remap register
	__vo uint32_t PMC;          // Peripheral mode configuration register
	__vo uint32_t EXTICR[4];    // External interrupt configuration registers BY MAKING ARRAY
	__vo uint32_t CMPCR;        // Compensation cell control register
} SYSCFG_RegDef_t;


typedef struct {
	__vo uint32_t IMR;     // Interrupt mask register
	__vo uint32_t EMR;     // Event mask register
	__vo uint32_t RTSR;    // Rising trigger selection register
	__vo uint32_t FTSR;    // Falling trigger selection register
	__vo uint32_t SWIER;   // Software interrupt event register
	__vo uint32_t PR;      // Pending register
} EXTI_RegDef_t;



typedef struct {
    __vo uint32_t CR;            // 0x00: Clock Control Register
    __vo uint32_t PLLCFGR;       // 0x04: PLL Configuration Register
    __vo uint32_t CFGR;          // 0x08: Clock Configuration Register
    __vo uint32_t CIR;           // 0x0C: Clock Interrupt Register
    __vo uint32_t AHB1RSTR;      // 0x10: AHB1 Peripheral Reset Register
    __vo uint32_t AHB2RSTR;      // 0x14: AHB2 Peripheral Reset Register
    __vo uint32_t AHB3RSTR;      // 0x18: AHB3 Peripheral Reset Register
    uint32_t      RESERVED0;     // 0x1C: Reserved
    __vo uint32_t APB1RSTR;      // 0x20: APB1 Peripheral Reset Register
    __vo uint32_t APB2RSTR;      // 0x24: APB2 Peripheral Reset Register
    uint32_t      RESERVED1[2];  // 0x28, 0x2C: Reserved
    __vo uint32_t AHB1ENR;       // 0x30: AHB1 Peripheral Clock Enable Register
    __vo uint32_t AHB2ENR;       // 0x34
    __vo uint32_t AHB3ENR;       // 0x38
    uint32_t      RESERVED2;     // 0x3C
    __vo uint32_t APB1ENR;       // 0x40
    __vo uint32_t APB2ENR;       // 0x44
    uint32_t      RESERVED3[2];  // 0x48, 0x4C
    __vo uint32_t AHB1LPENR;     // 0x50: AHB1 Low Power Clock Enable Register
    __vo uint32_t AHB2LPENR;     // 0x54
    __vo uint32_t AHB3LPENR;     // 0x58
    uint32_t      RESERVED4;     // 0x5C
    __vo uint32_t APB1LPENR;     // 0x60
    __vo uint32_t APB2LPENR;     // 0x64
    uint32_t      RESERVED5[2];  // 0x68, 0x6C
    __vo uint32_t BDCR;          // 0x70
    __vo uint32_t CSR;           // 0x74
    uint32_t      RESERVED6[2];  // 0x78, 0x7C
    __vo uint32_t SSCGR;         // 0x80
    __vo uint32_t PLLI2SCFGR;    // 0x84
    __vo uint32_t PLLSAICFGR;    // 0x88 (optional, on STM32F42x/F43x)
    __vo uint32_t DCKCFGR;       // 0x8C
} RCC_RegDef_t;






/*
 * Now defining Clock enable MACROS FOR GPIOx.
 * Here i will make Macro as a function to use/call easily.
 */
// Function-style macros
#define RCC_GPIOA_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 0))
#define RCC_GPIOB_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 1))
#define RCC_GPIOC_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 2))
#define RCC_GPIOD_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 3))
#define RCC_GPIOE_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 4))

#define RCC_GPIOF_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 5))
#define RCC_GPIOG_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 6))
#define RCC_GPIOH_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 7))
#define RCC_GPIOI_CLK_ENABLE()   (RCC->AHB1ENR |= (1U << 8))
/*
 * clock enable Macros for I2Cx peripherals.
 */
// Function-style macros to enable clocks for I2C peripherals
#define RCC_I2C1_CLK_ENABLE()    (RCC->APB1ENR |= (1U << 21))
#define RCC_I2C2_CLK_ENABLE()    (RCC->APB1ENR |= (1U << 22))
#define RCC_I2C3_CLK_ENABLE()    (RCC->APB1ENR |= (1U << 23))

/*
 * clock enable Macros for SPIx peripherals.
 */

#define RCC_SPI1_CLK_ENABLE()    (RCC->APB2ENR |= (1U << 12))
#define RCC_SPI2_CLK_ENABLE()   (RCC->APB1ENR |= (1U << 14))
#define RCC_SPI3_CLK_ENABLE()   (RCC->APB1ENR |= (1U << 15))

/*
 * clock enable Macros for USARTx peripherals.
 */
#define RCC_USART1_CLK_ENABLE()    (RCC->APB2ENR |= (1U << 4))
#define RCC_USART2_CLK_ENABLE()    (RCC->APB1ENR |= (1U << 17))

/*
 * clock enable Macros for SYSCNFGx peripherals.
 */
#define RCC_SYSCFG_CLK_ENABLE()   (RCC->APB2ENR |= (1U << 14))

// Add more as needed...




/*
 * now i will write Macros to disable the Peripherals.
 * starting with GPIOx
 */
// Macros to DISABLE clocks for GPIOx peripherals on AHB1 bus
#define RCC_GPIOA_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 0))
#define RCC_GPIOB_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 1))
#define RCC_GPIOC_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 2))
#define RCC_GPIOD_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 3))
#define RCC_GPIOE_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 4))
#define RCC_GPIOF_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 5))
#define RCC_GPIOG_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 6))
#define RCC_GPIOH_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 7))
#define RCC_GPIOI_CLK_DISABLE()   (RCC->AHB1ENR &= ~(1U << 8))


// Function-style macros to disable clocks for I2C peripherals
#define RCC_I2C1_CLK_DISABLE()    (RCC->APB1ENR &= ~(1U << 21))
#define RCC_I2C2_CLK_DISABLE()    (RCC->APB1ENR &= ~(1U << 22))
#define RCC_I2C3_CLK_DISABLE()    (RCC->APB1ENR &= ~(1U << 23))

// Function-style macros to disable clocks for SPI peripherals
#define RCC_SPI1_CLK_DISABLE()   (RCC->APB2ENR &= ~(1U << 12))
#define RCC_SPI2_CLK_DISABLE()   (RCC->APB1ENR &= ~(1U << 14))
#define RCC_SPI3_CLK_DISABLE()   (RCC->APB1ENR &= ~(1U << 15))


//clock disable Macros for SPIx peripherals.
#define RCC_SPI1_CLK_DISABLE()    (RCC->APB2ENR &= ~(1U << 12))


// Function-style macros to disable clocks for USART/UART peripherals
#define RCC_USART1_CLK_DISABLE()   (RCC->APB2ENR &= ~(1U << 4))
#define RCC_USART2_CLK_DISABLE()   (RCC->APB1ENR &= ~(1U << 17))

// clock Disable Macros for SYSCNFGx peripherals.
#define RCC_SYSCFG_CLK_DISABLE()   (RCC->APB2ENR &= ~(1U << 14))


// MACROS TO RESET THE GPIOX PERIPHERALS
#define GPIOA_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 0)); (RCC->AHB1RSTR &= ~(1U << 0)); } while(0)
#define GPIOB_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 1)); (RCC->AHB1RSTR &= ~(1U << 1)); } while(0)
#define GPIOC_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 2)); (RCC->AHB1RSTR &= ~(1U << 2)); } while(0)
#define GPIOD_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 3)); (RCC->AHB1RSTR &= ~(1U << 3)); } while(0)
#define GPIOE_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 4)); (RCC->AHB1RSTR &= ~(1U << 4)); } while(0)
#define GPIOF_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 5)); (RCC->AHB1RSTR &= ~(1U << 5)); } while(0)
#define GPIOG_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 6)); (RCC->AHB1RSTR &= ~(1U << 6)); } while(0)
#define GPIOH_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 7)); (RCC->AHB1RSTR &= ~(1U << 7)); } while(0)
#define GPIOI_REG_RESET()    do { (RCC->AHB1RSTR |= (1U << 8)); (RCC->AHB1RSTR &= ~(1U << 8)); } while(0)




#define ENABLE 			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define GPIO_PIN_SET	SET
#define GPIO_PIN_RESET	RESET
#define FLAG_RESET		RESET
#define FLAG_SET		SET

#include "stm32f401xx_GPIO_drive.h"
#include"stm32f4_01SPI_driver.h"

#endif /* MY_INC_STM32_F401RE_H_ */
