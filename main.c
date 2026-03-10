/*
 * main.c
 *
 *  Created on: Aug 4, 2025
 *      Author: MZH9PH
 */

#include "stm32_f401re.h"
#include "stm32f401xx_GPIO_drive.h"
#define LOW 0
#define BTN_PRESSED LOW

void delay(void)
{
	for (uint32_t i= 0; i <500000 ; i++);
}

int main(void)
{
	GPIO_Handle_t GpioLed;
	GPIO_Handle_t GpioSwitch;
	GPIO_Handle_t Gpio_BOARD_LED;


	/* --- Configure PA6 as output (controlled by PA9) --- */
	GpioLed.pGPIOx = GPIOA;
	GpioLed.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_6;
	GpioLed.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	GpioLed.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	GpioLed.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	GpioLed.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

	/* --- Configure PA5 as output (controlled by PA9) --- */
	Gpio_BOARD_LED.pGPIOx = GPIOA;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_5;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD;
	Gpio_BOARD_LED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;

    /* --- Configure PA9 as input (Switch) --- */
    GpioSwitch.pGPIOx = GPIOA;
    GpioSwitch.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_9;
    GpioSwitch.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GpioSwitch.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_PIN_PU; // PULL-Up



	GPIO_PeripheralClockControl(GPIOA, ENABLE);

	GPIO_Init(&GpioLed);
	GPIO_Init(&GpioSwitch);
	GPIO_Init(&Gpio_BOARD_LED);



	while(1)
	{



		if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_9) == BTN_PRESSED)
		{
			GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_6, 1);
			GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_5, 1);
			delay();
			//GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_5);
			//GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_6);

		}
		else
		{
			GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_6, 0);
			GPIO_WriteToOutputPin(GPIOA, GPIO_PIN_5, 0);
		}
	}
	return 0;
}


// ISR IMPLEMENTATION. No input or output. It just handle the interrupt
void EXTI0_IRQHandler (void)
{
	GPIO_IRQHandling (0);

}
