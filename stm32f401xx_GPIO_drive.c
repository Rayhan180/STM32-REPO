/*
 * stm32f401xx_GPIO_drive.c
 *
 *  Created on: Aug 5, 2025
 *      Author: MZH9PH
 */

#include "stm32f401xx_GPIO_drive.h"

/**
 * @brief  Enables or disables the AHB1 peripheral clock for the specified GPIO port.
 *
 * @param  pGPIOx  Pointer to the GPIO peripheral base address (e.g., GPIOA, GPIOB).
 * @param  EnOrDi  Enable or disable option:
 *                 - 1 : Enable peripheral clock
 *                 - 0 : Disable peripheral clock
 *
 * @return None
 *
 * @note   This function controls the corresponding bit in RCC->AHB1ENR for the given GPIO port.
 *         - The GPIO port clock **must be enabled** before configuring or using any of its pins,
 *           otherwise register writes will have no effect.
 *         - Disabling the clock stops the peripheral, reduces power consumption,
 *           and prevents further register access until re-enabled.
 *         - Passing an invalid GPIO base address will result in undefined behavior.
 *         - This function does not configure the pins themselves; it only controls the port's clock.
 */
void GPIO_PeripheralClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnOrDi) {
	if (EnOrDi == ENABLE) {
		if (pGPIOx == GPIOA) {
			RCC_GPIOA_CLK_ENABLE();
		} else if (pGPIOx == GPIOB) {
			RCC_GPIOB_CLK_ENABLE();
		} else if (pGPIOx == GPIOC) {
			RCC_GPIOC_CLK_ENABLE();
		} else if (pGPIOx == GPIOD) {
			RCC_GPIOD_CLK_ENABLE();
		} else if (pGPIOx == GPIOE) {
			RCC_GPIOE_CLK_ENABLE();
		} else if (pGPIOx == GPIOF) {
			RCC_GPIOF_CLK_ENABLE();
		} else if (pGPIOx == GPIOG) {
			RCC_GPIOG_CLK_ENABLE();
		} else if (pGPIOx == GPIOH) {
			RCC_GPIOH_CLK_ENABLE();
		} else if (pGPIOx == GPIOI) {
			RCC_GPIOI_CLK_ENABLE();
		}
		/* else: invalid base address */
	} else /* DISABLE */
	{
		if (pGPIOx == GPIOA) {
			RCC_GPIOA_CLK_DISABLE();
		} else if (pGPIOx == GPIOB) {
			RCC_GPIOB_CLK_DISABLE();
		} else if (pGPIOx == GPIOC) {
			RCC_GPIOC_CLK_DISABLE();
		} else if (pGPIOx == GPIOD) {
			RCC_GPIOD_CLK_DISABLE();
		} else if (pGPIOx == GPIOE) {
			RCC_GPIOE_CLK_DISABLE();
		} else if (pGPIOx == GPIOF) {
			RCC_GPIOF_CLK_DISABLE();
		} else if (pGPIOx == GPIOG) {
			RCC_GPIOG_CLK_DISABLE();
		} else if (pGPIOx == GPIOH) {
			RCC_GPIOH_CLK_DISABLE();
		} else if (pGPIOx == GPIOI) {
			RCC_GPIOI_CLK_DISABLE();
		}
		/* else: invalid base address */
	}
}

/**
 * @brief  Initializes the specified GPIO pin(s) according to the configuration in the handle.
 *
 * @param  pGPIOHandler  Pointer to a GPIO handle structure that contains:
 *                       - The base address of the GPIO port to configure.
 *                       - The pin configuration settings (mode, speed, pull-up/down, output type, alternate function).
 *
 * @return None
 *
 * @note   This function:
 *         - Enables the peripheral clock for the specified GPIO port if not already enabled.
 *         - Configures the pin mode (input, output, alternate function, analog).
 *         - Sets the output type (push-pull or open-drain).
 *         - Configures the output speed (low, medium, fast, high).
 *         - Enables/disables internal pull-up or pull-down resistors.
 *         - Configures the alternate function registers if the mode is set to alternate function.
 *         - Must be called before using the pin for input/output operations.
 *         - Will overwrite any previous configuration of the specified pin(s).
 *         - Does not perform any runtime safety checks on pin validity — invalid configuration may lead to undefined behavior.
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandler) {
	// configuring the mode of gpio
	uint32_t temp = 0;
	// enable the clock peripheral
	GPIO_PeripheralClockControl (pGPIOHandler->pGPIOx, ENABLE);

	// configure the mode of gpio pin
	if (pGPIOHandler->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) {
		temp = (pGPIOHandler->GPIO_PinConfig.GPIO_PinMode
				<< (2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandler->pGPIOx->MODER &= ~(0x3
				<< (2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber)); // clearing , I ADDED 2 *
		pGPIOHandler->pGPIOx->MODER |= temp;
	} else {

		// this part is interrupT mode CONFIGURATION
		if (pGPIOHandler->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT) {
			// Configure the Falling Trigger Selection Register (FTSR)
			EXTI->FTSR |= (1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR &= ~(1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber); // disable rising edge if previously set
		} else if (pGPIOHandler->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT) {
			// Configure the Rising Trigger Selection Register (RTSR)
			EXTI->RTSR |= (1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR &= ~(1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber); // disable falling edge if previously set
		} else if (pGPIOHandler->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT) {
			// Configure both Falling and Rising edge
			EXTI->FTSR |= (1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->RTSR |= (1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
		}
		//2. CONFIGURE THE GPIO PORT SELECTION IN SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber / 4; // EXTICR register index (0-3)
		uint8_t temp2 = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber % 4; // Position inside EXTICR (0-3)
		uint8_t portCode = GPIO_BASEADDR_TO_CODE(pGPIOHandler->pGPIOx); // Map GPIO base to code (0-7)
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] &= ~(0xF << (temp2 * 4));   // Clear previous bits
		SYSCFG->EXTICR[temp1] |= (portCode << (temp2 * 4)); // Set new port

		// 3. Enable interrupt delivery using IMR
		EXTI->IMR |= (1 << pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);

	}

	temp = 0;
	// configuring the speed
	temp = (pGPIOHandler->GPIO_PinConfig.GPIO_PinSpeed
			<< (2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandler->pGPIOx->OSPEED &= ~(0x3
			<< (2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber)); // clearing
	pGPIOHandler->pGPIOx->OSPEED |= temp; //setting
	temp = 0;

	// configuring the PUPD settings.
	temp = (pGPIOHandler->GPIO_PinConfig.GPIO_PinPuPdControl
			<< (2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber));
	pGPIOHandler->pGPIOx->PUPDR &= ~(0x3
			<< (2 * pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber)); // clearing
	pGPIOHandler->pGPIOx->PUPDR |= temp; //setting
	temp = 0;
	// configuring the OPTYPE
	temp = (pGPIOHandler->GPIO_PinConfig.GPIO_PinOPType
			<< pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber);
	pGPIOHandler->pGPIOx->OTYPER &= ~(0x3
			<< pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber); // clearing
	pGPIOHandler->pGPIOx->OTYPER |= temp; //setting
	temp = 0;
	// configuring the alt functionality
	if (pGPIOHandler->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
		uint8_t temp1, temp2;
		temp1 = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber / 8;
		temp2 = pGPIOHandler->GPIO_PinConfig.GPIO_PinNumber % 8;
		pGPIOHandler->pGPIOx->AFR[temp1] &= ~(0xF << (4 * temp2)); //clearing
		pGPIOHandler->pGPIOx->AFR[temp1] |=
				(pGPIOHandler->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * temp2)); //setting

	}

}

/* Resets the specified GPIO port to its default state. we can reset all the gpio using RCC AHB1 reset peripheral.
 * @fn     void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)
 * @brief  Resets the specified GPIO port to its default state.
 *
 * @param  pGPIOx : Pointer to GPIO peripheral base address (e.g., GPIOA, GPIOB).
 *
 * @return None
 *
 * @note   This function uses RCC->AHB1RSTR to reset the GPIO.
 *         It affects all pins in the port, not individual pins.
 */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) {
	if (pGPIOx == GPIOA) {
		GPIOA_REG_RESET();
	} else if (pGPIOx == GPIOB) {
		GPIOB_REG_RESET();
	} else if (pGPIOx == GPIOC) {
		GPIOC_REG_RESET();
	} else if (pGPIOx == GPIOD) {
		GPIOD_REG_RESET();
	} else if (pGPIOx == GPIOE) {
		GPIOE_REG_RESET();
	} else if (pGPIOx == GPIOF) {
		GPIOF_REG_RESET();
	} else if (pGPIOx == GPIOG) {
		GPIOG_REG_RESET();
	} else if (pGPIOx == GPIOH) {
		GPIOH_REG_RESET();
	} else if (pGPIOx == GPIOI) {
		GPIOI_REG_RESET();
	}

}

/**
 * @brief  Reads the logic level from a specific GPIO input pin.
 *
 * @param  pGPIOx     Pointer to the GPIO peripheral base address (e.g., GPIOA, GPIOB).
 * @param  PinNumber  GPIO pin number to read (0–15).
 *
 * @return uint8_t    Logic level of the specified pin:
 *                    - 0 : Pin is at logic low level
 *                    - 1 : Pin is at logic high level
 *
 * @note   This function:
 *         - Reads the value of the IDR (Input Data Register) for the specified port.
 *         - Shifts and masks the result to isolate the specified pin.
 *         - Works only if the pin is configured as an input or alternate function that outputs to the pin.
 *         - Can return the value as `uint8_t` or `bool` depending on coding style preference.
 *         - The actual voltage threshold for high/low is determined by the MCU's input circuitry.
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) // it should return 0 or 1. can use Boolean or uint 8.
{
	uint8_t value;
	value = (uint8_t) ((pGPIOx->IDR >> PinNumber) & 0x00000001);
	return value;

}

/**
 * @brief  Reads the logic levels from all pins of the specified GPIO port.
 *
 * @param  pGPIOx  Pointer to the GPIO peripheral base address (e.g., GPIOA, GPIOB).
 *
 * @return uint16_t  A 16-bit value representing the logic state of all pins:
 *                   - Bit 0 → Pin 0 state
 *                   - Bit 1 → Pin 1 state
 *                   - ...
 *                   - Bit 15 → Pin 15 state
 *                   Each bit will be:
 *                   - 0 : Corresponding pin is at logic low level
 *                   - 1 : Corresponding pin is at logic high level
 *
 * @note   This function:
 *         - Directly returns the value of the IDR (Input Data Register) for the given port.
 *         - Useful when reading multiple pins at once instead of checking each individually.
 *         - Works only for pins configured as inputs or alternate functions that output to the pin.
 *         - The actual voltage thresholds for high/low are determined by the MCU's input circuitry.
 */

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) // here it is 16 bit port.
{
	uint16_t value;
	value = (uint16_t) (pGPIOx->IDR);
	return value;
}
// Reads the value from a specific Outputt pin (placeholder format)
/**
 * @brief  Reads the logic level currently being driven on a specific GPIO output pin.
 *
 * @param  pGPIOx     Pointer to the GPIO peripheral base address (e.g., GPIOA, GPIOB).
 * @param  PinNumber  GPIO pin number to read (0–15).
 *
 * @return uint8_t    Logic level of the specified output pin:
 *                    - 0 : Pin is at logic low level
 *                    - 1 : Pin is at logic high level
 *
 * @note   This function:
 *         - Reads the value from the ODR (Output Data Register) for the given port.
 *         - Returns the level that the MCU is currently driving, not the actual physical voltage
 *           on the pin (use `GPIO_ReadFromInputPin` to sample the real pin state).
 *         - Works only if the pin is configured as an output or is under software control
 *           in alternate function mode.
 *         - The `PinNumber` must be between 0 and 15; out-of-range values result in undefined behavior.
 */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber,
		uint8_t value) // it should return 0 or 1. can use Boolean or uint 8.
{
	if (value == GPIO_PIN_SET) {
		// WRITE 1 TO THE OUTPUT DATA REGISTER AT THE BIT FIELD CORRESPPNDING TO THE PIN NUMBER
		pGPIOx->ODR |= (1 << PinNumber);
	} else {
		//write 0
		pGPIOx->ODR &= ~(1 << PinNumber);
	}

}

// Writes a value (HIGH or LOW) to a specific output pin

/**
 * @brief  Writes logic levels to one or more pins of the specified GPIO port.
 *
 * @param  pGPIOx     Pointer to the GPIO peripheral base address (e.g., GPIOA, GPIOB).
 * @param  PinNumber  Bit mask indicating which pin(s) to modify (bit 0 = Pin 0, bit 1 = Pin 1, ...).
 *                    - To target a single pin, set only its corresponding bit (e.g., `1U << 5` for Pin 5).
 *                    - To target multiple pins, combine bits with bitwise OR (e.g., `(1U << 0) | (1U << 3)`).
 * @param  Value      Bit mask representing the desired logic level(s) for the selected pin(s):
 *                    - Bit = 0 : Drive corresponding pin low
 *                    - Bit = 1 : Drive corresponding pin high
 *
 * @return None
 *
 * @note   This function:
 *         - Updates only the specified pin(s) in the ODR (Output Data Register) for the given port.
 *         - Does not affect other pins in the port.
 *         - Can be used to write to multiple pins in a single operation.
 *         - The `PinNumber` parameter acts as a mask to select which bits in the ODR are updated.
 *         - For atomic set/reset operations without read-modify-write, consider using the BSRR register instead.
 */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t value) // here it is 16 bit port. This can take Pin set or reset value.
{
	pGPIOx->ODR = value;

}

// Toggles the current state of an output pin
/**
 * @brief  Writes logic levels to one or more pins of the specified GPIO port.
 *
 * @param  pGPIOx     Pointer to the GPIO peripheral base address (e.g., GPIOA, GPIOB).
 * @param  PinNumber  Bit mask indicating which pin(s) to modify (bit 0 = Pin 0, bit 1 = Pin 1, ...).
 *                    - To target a single pin, set only its corresponding bit (e.g., `1U << 5` for Pin 5).
 *                    - To target multiple pins, combine bits with bitwise OR (e.g., `(1U << 0) | (1U << 3)`).
 * @param  Value      Bit mask representing the desired logic level(s) for the selected pin(s):
 *                    - Bit = 0 : Drive corresponding pin low
 *                    - Bit = 1 : Drive corresponding pin high
 *
 * @return None
 *
 * @note   This function:
 *         - Updates only the specified pin(s) in the ODR (Output Data Register) for the given port.
 *         - Does not affect other pins in the port.
 *         - Can be used to write to multiple pins in a single operation.
 *         - The `PinNumber` parameter acts as a mask to select which bits in the ODR are updated.
 *         - For atomic set/reset operations without read-modify-write, consider using the BSRR register instead.
 */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
	pGPIOx->ODR ^= (1 << PinNumber);
}

/**
 * @brief  Configures (enables or disables) the interrupt line for a specific IRQ number and sets its priority.
 *
 * @param  IRQNumber   Interrupt request (IRQ) number for the GPIO EXTI line or other peripheral.
 *                     - Refer to the device's vector table for valid IRQ numbers.
 * @param  IRQPriority Priority level for the interrupt (lower number = higher priority).
 *                     - Valid range depends on the MCU's NVIC priority bits (typically 0–15).
 * @param  EnorDi      Enable or disable flag:
 *                     - 1 : Enable the interrupt in the NVIC
 *                     - 0 : Disable the interrupt in the NVIC
 *
 * @return None
 *
 * @note   This function:
 *         - Uses NVIC ISER (Interrupt Set-Enable Registers) to enable the given IRQ number.
 *         - Uses NVIC ICER (Interrupt Clear-Enable Registers) to disable the given IRQ number.
 *         - Does not configure the EXTI (external interrupt) trigger source or mode — that must be set separately.
 *         - Must be called after properly configuring the GPIO pin for interrupt mode (input, pull-up/down, etc.).
 *         - Invalid IRQ numbers or priorities outside the supported range result in undefined behavior.
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi) {
	if (EnorDi == ENABLE) {
		// 1. Enable interrupt in ISERx (Interrupt Set-Enable Register)
		if (IRQNumber <= 31) {
			*NVIC_ISER0 |= (1 << IRQNumber);        // ISER0 handles IRQ 0-31
		} else if (IRQNumber > 31 && IRQNumber < 64) {
			*NVIC_ISER1 |= (1 << (IRQNumber % 32)); // ISER1 handles IRQ 32-63
		} else if (IRQNumber > 64 && IRQNumber < 96) {
			*NVIC_ISER2 |= (1 << (IRQNumber % 64)); // ISER2 handles IRQ 64-95
		}
	} else {
		// 2. Disable interrupt in ICERx (Interrupt Clear-Enable Register)
		if (IRQNumber <= 31) {
			*NVIC_ICER0 |= (1 << IRQNumber);
		} else if (IRQNumber > 31 && IRQNumber < 64) {
			*NVIC_ICER1 |= (1 << (IRQNumber % 32));
		} else if (IRQNumber > 64 && IRQNumber < 96) {
			*NVIC_ICER2 |= (1 << (IRQNumber - 64)); // i can subtract. just a example.
		}
	}

}

// Configures the interrupt priority by writing to NVIC_IPR (Interrupt Priority Registers).
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority) {
	//lets find out the ipr regIster
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
	uint8_t shift_amount = (8 * iprx_section) + (8 - NO_PR_BITS_IMPLEMENTATED);
	*(NVIC_IPR_BASE_ADDR + iprx) |= (IRQPriority << (8 * shift_amount));
}

/**
 * @brief  Handles the interrupt event for the specified GPIO pin.
 *
 * @param  PinNumber  GPIO pin number (0–15) that triggered the interrupt.
 *
 * @return None
 *
 * @note   This function:
 *         - Checks the EXTI (External Interrupt) Pending Register (PR) for the specified pin.
 *         - If the pending bit for the pin is set, it clears it by writing 1 to the same bit.
 *         - Must be called inside the corresponding IRQ handler in the vector table (e.g., EXTI0_IRQHandler).
 *         - Does not perform any debounce or filtering — if needed, that must be implemented separately.
 *         - Should be called after the source of the interrupt has been serviced, to avoid re-triggering.
 *         - Clearing the pending bit is mandatory; otherwise, the interrupt will fire repeatedly.
 */
void GPIO_IRQHandling(uint8_t PinNumber) {
	if (EXTI->PR & (1 << PinNumber)) {
		EXTI->PR |= (1 << PinNumber); // CLEAR
	}

}
