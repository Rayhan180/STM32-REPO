/*
 * button_interrupt.c
 *
 *  Created on: Sep 1, 2025
 *      Author: MZH9PH
 */

#include<string.h>
#include "stm32_f401re.h"
#include "stm32f401xx_GPIO_drive.h"
#define LOW 0
#define HIGH 1
#define BTN_PRESSED LOW


void delay(void)
{
	for (uint32_t i= 0; i <500000/2 ; i++);
}

int main(void)
{
	GPIO_Handle_t Gpio_Board_Switch;
	GPIO_Handle_t Gpio_BOARD_LED;
	GPIO_Handle_t GpioSwitch;
	memset(&Gpio_BOARD_LED, 0 , sizeof(Gpio_BOARD_LED));
	memset(&GpioSwitch, 0 , sizeof(GpioSwitch));


	/* --- Configure PA5 as output (LED CONNECTED TO BOARD) --- */
	Gpio_BOARD_LED.pGPIOx = GPIOA;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /* --- Configure PC13 as input (Switch connected to BOARD) --- */
    Gpio_Board_Switch.pGPIOx = GPIOC;
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_13;
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT; // INTERRUPT FALLING EDGE
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU;
    Gpio_Board_Switch.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /* --- Configure PA9 as input (Switch) --- */
    GpioSwitch.pGPIOx = GPIOA;
    GpioSwitch.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_9;
    GpioSwitch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IT_FT;
    GpioSwitch.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; // PULL-Up
    GpioSwitch.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;



	GPIO_PeripheralClockControl(GPIOA, ENABLE);
	GPIO_PeripheralClockControl(GPIOC, ENABLE);


	GPIO_Init(&Gpio_Board_Switch);
	GPIO_Init(&Gpio_BOARD_LED);
	GPIO_Init(&GpioSwitch);

//	// IRQ configuration FOR SWITCH ON BOARD
//	GPIO_IRQInterruptConfig( IRQ_NO_EXTI15_10, ENABLE);
//	// PRIORITY CONFIGURATION
//	GPIO_IRQPriorityConfig(IRQ_NO_EXTI15_10, NVIC_IRQ_PRIORITY15);

	// IRQ configuration FOR PIN GPOIA9
	GPIO_IRQInterruptConfig( IRQ_NO_EXTI9_5, ENABLE);
	// PRIORITY CONFIGURATION
	GPIO_IRQPriorityConfig(IRQ_NO_EXTI9_5, NVIC_IRQ_PRIORITY9);

	return 0;
}

void EXTI9_5_IRQHandler(void)
{
	GPIO_IRQHandling(GPIO_PIN_9);
	GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);

}

